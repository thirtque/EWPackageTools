#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

#include <zstd.h>

#include "buffer.h"
#include "image.h"

namespace Package {
    struct EntryInformation {
        std::string Name;
        uint32_t Position;
        uint32_t Compression;
        uint32_t UncompressedLength;
        uint32_t Length;
    };

    enum class EntryType {
        Binary,
        Text,
        ImagePng,
        ImageHmg,
    };

    struct Entry {
        bool Opened;
        bool Selected;
        EntryType Type;
        EntryInformation Information;
        std::vector<uint8_t> *Data;
        Image::Texture Texture;
    };

    struct PackageHeader {
        uint32_t Signature;
        uint32_t EntryCount;
    };

    struct Package {
        PackageHeader Header;
        std::vector<Entry> Entries;
    };

    Package ReadPackage(std::ifstream &packageFile);
    //Package WritePackage(std::ofstream &packageFile);

    //Entry ReadEntry(std::ifstream &entryFile);
    void WriteEntry(std::ofstream &entryFile, const Entry &entry);
}