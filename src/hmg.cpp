#include "hmg.h"

namespace Hmg {
    void Decode(const std::vector<uint8_t> &hmgData, std::vector<uint8_t> &imageData, unsigned &imageWidth, unsigned &imageHeight) {
        auto offsetWidth = 3 + 1 + 8 + hmgData[3];
        auto offsetHeight = offsetWidth + 4;
        auto _o = offsetHeight + 4 + 2;
        auto offsetData = _o + 2 + hmgData[_o];

        imageWidth = Buffer::ReadUint32(hmgData.data() + offsetWidth);
        imageHeight = Buffer::ReadUint32(hmgData.data() + offsetHeight);

        imageData.resize(imageWidth * imageHeight * 4);

        LZ4_decompress_safe(
                reinterpret_cast<const char *>(hmgData.data() + offsetData),
                reinterpret_cast<char *>(imageData.data()),
                hmgData.size() - offsetData,
                imageData.size()
        );
    }

    void ConvertToPng(const std::vector<uint8_t> &hmgData, std::vector<uint8_t> &pngData) {
        auto imageData = new std::vector<uint8_t>();
        uint32_t imageWidth;
        uint32_t imageHeight;

        Decode(hmgData, *imageData, imageWidth, imageHeight);

        lodepng::encode(pngData, *imageData, imageWidth, imageHeight);

        delete imageData;
    }
}