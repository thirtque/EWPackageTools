#pragma once

#include <vector>
#include <cstdint>
#include <lodepng.h>

#include "lz4.h"

#include "buffer.h"

namespace Hmg {
    void Decode(const std::vector<uint8_t> &hmgData, std::vector<uint8_t> &imageData, unsigned &imageWidth, unsigned &imageHeight);
    void ConvertToPng(const std::vector<uint8_t> &hmgData, std::vector<uint8_t> &pngData);
}