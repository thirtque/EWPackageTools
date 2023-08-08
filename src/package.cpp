#include "package.h"

namespace Package {
    // @todo Implement read error handling
    PackageHeader ReadPackageHeader(std::ifstream &packageFile) {
        std::array<uint8_t, 8> buffer{};
        packageFile.read(reinterpret_cast<char *>(buffer.data()), buffer.size());

        uint32_t packageHeader = Buffer::ReadUint32(buffer.data());
        uint32_t packageEntryCount = Buffer::ReadUint32(buffer.data() + 4);

        return {packageHeader, packageEntryCount};
    }

    // Buffer size assumes maximum entry name length of 240 characters
    constexpr uint32_t packageEntryBufferSize = 256;
    constexpr uint32_t packageEntryInformationSize = 16;

    // @todo Implement read error handling
    EntryInformation ReadPackageEntry(std::ifstream &packageFile) {
        std::array<uint8_t, packageEntryBufferSize> buffer{};

        for (auto b = 0, p = 0; b < packageEntryBufferSize; b += packageEntryInformationSize) {
            packageFile.read(reinterpret_cast<char *>(buffer.data() + b), packageEntryInformationSize);

            for (auto bo = 0; bo < packageEntryInformationSize; bo++, p++) {
                // Find null terminator in entry name
                if (buffer[p] != 0) {
                    continue;
                }

                // Read missing bytes for entry information
                packageFile.read(reinterpret_cast<char *>(buffer.data() + b + packageEntryInformationSize), bo + 1);

                // Deserialize entry name
                std::string entryName(reinterpret_cast<const char *>(buffer.data()), p);

                // Skip null terminator
                p++;

                // Deserialize entry information
                uint32_t offset = Buffer::ReadUint32(buffer.data() + p);
                uint32_t compression = Buffer::ReadUint32(buffer.data() + p + 4);
                uint32_t uncompressedLength = Buffer::ReadUint32(buffer.data() + p + 8);
                uint32_t length = Buffer::ReadUint32(buffer.data() + p + 12);

                return {entryName, offset, compression, uncompressedLength, length};
            }
        }

        return {};
    }

    bool EntryDataIsImagePng(std::vector<uint8_t> *entryData) {
        return entryData->size() > 8
                && (*entryData)[0] == 0x89
                && (*entryData)[1] == 0x50
                && (*entryData)[2] == 0x4e
                && (*entryData)[3] == 0x47
                && (*entryData)[4] == 0x0d
                && (*entryData)[5] == 0x0a
                && (*entryData)[6] == 0x1a
                && (*entryData)[7] == 0x0a;
    }

    bool EntryDataIsImageHmg(std::vector<uint8_t> *entryData) {
        return entryData->size() > 3
                && (*entryData)[0] == 0x50
                && (*entryData)[1] == 0x47
                && (*entryData)[2] == 0x46;
    }

    bool EntryDataIsText(std::vector<uint8_t> *entryData) {
        const static std::array<uint8_t, 2> printableChars = {0x0A, 0x09};

        return std::ranges::all_of(*entryData, [](uint8_t b) {
            return std::isprint(static_cast<unsigned char>(b))
                    || std::ranges::find(printableChars, b) != printableChars.end();
        });
    }

    EntryType DetectEntryType(std::vector<uint8_t> *entryData) {
        if (EntryDataIsImagePng(entryData)) {
            return EntryType::ImagePng;
        }
        if (EntryDataIsImageHmg(entryData)) {
            return EntryType::ImageHmg;
        }
        if (EntryDataIsText(entryData)) {
            return EntryType::Text;
        }
        return EntryType::Binary;
    }

    // @todo Implement read error handling
    Package ReadPackage(std::ifstream &packageFile) {
        PackageHeader packageHeader = ReadPackageHeader(packageFile);
        if (packageHeader.Signature != 0x6A37) {
            // @todo Invalid header error
        }

        std::vector<Entry> entries(packageHeader.EntryCount);
        for (auto &entry: entries) {
            entry.Information = ReadPackageEntry(packageFile);
        }

        for (auto &entry: entries) {
            const auto &entryInformation = entry.Information;

            entry.Data = new std::vector<uint8_t>(entryInformation.Length);

            packageFile.seekg(entryInformation.Position, std::ios_base::beg);
            packageFile.read(reinterpret_cast<char *>(entry.Data->data()), entry.Data->size());

            if (entryInformation.Compression == 2) {
                auto *uncompressedEntryData = new std::vector<uint8_t>(entryInformation.UncompressedLength);
                ZSTD_decompress(uncompressedEntryData->data(), uncompressedEntryData->size(), entry.Data->data(),
                        entry.Data->size());
                delete entry.Data;
                entry.Data = uncompressedEntryData;
            }

            entry.Type = DetectEntryType(entry.Data);
        }

        return {packageHeader, entries};
    }

    void WritePackageHeader(std::ofstream &packageFile, PackageHeader &packageHeader) {
        std::array<uint8_t, 8> buffer{};

        Buffer::WriteUint32(buffer.data(), packageHeader.Signature);
        Buffer::WriteUint32(buffer.data() + 4, packageHeader.EntryCount);

        packageFile.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
    }

    void WritePackageEntry(std::ofstream &packageFile, uint32_t entryOffset, Entry &entry) {
        packageFile.write(entry.Information.Name.c_str(), entry.Information.Name.length() + 1);

        std::array<uint8_t, packageEntryInformationSize> buffer{};

        Buffer::WriteUint32(buffer.data(), entryOffset);
        Buffer::WriteUint32(buffer.data() + 4, 0);
        Buffer::WriteUint32(buffer.data() + 8, entry.Data->size());
        Buffer::WriteUint32(buffer.data() + 12, entry.Data->size());

        packageFile.write(reinterpret_cast<char *>(buffer.data()), buffer.size());
    }

    void WritePackage(std::ofstream &packageFile, Package &package) {
        WritePackageHeader(packageFile, package.Header);

        uint32_t entryOffset = 0;
        entryOffset += 8; // Header size
        for (auto &entry: package.Entries) {
            entryOffset += entry.Information.Name.length() + 1; // Entry name length
            entryOffset += 16; // Entry header size
        }

        for (auto &entry: package.Entries) {
            WritePackageEntry(packageFile, entryOffset, entry);
            entryOffset += entry.Data->size();
        }

        for (auto &entry: package.Entries) {
            packageFile.write(reinterpret_cast<char *>(entry.Data->data()), entry.Data->size());
        }
    }

    void WriteEntry(std::ofstream &entryFile, const Entry &entry) {
        entryFile.write(reinterpret_cast<char *>(entry.Data->data()), entry.Data->size());
    }

    void ReadEntry(std::ifstream &entryFile, const Entry &entry) {
        std::array<uint8_t, 1024> buffer{};
        entry.Data->clear();
        while (true) {
            entryFile.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
            auto n = entryFile.gcount();
            if (n < buffer.size()) {
                entry.Data->insert(entry.Data->end(), std::begin(buffer), std::begin(buffer) + n);
                break;
            } else {
                entry.Data->insert(entry.Data->end(), std::begin(buffer), std::end(buffer));
            }
        }
    }
}