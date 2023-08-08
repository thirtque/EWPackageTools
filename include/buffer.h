#pragma once

#include <cstdint>

namespace Buffer {
    uint32_t ReadUint32(const uint8_t *b);

    void WriteUint32(uint8_t *b, uint32_t value);
}