#include "buffer.h"

namespace Buffer {
    uint32_t ReadUint32(const uint8_t *b) {
        return b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    }

    void WriteUint32(uint8_t *b, uint32_t value) {
        b[0] = value & 0xff;
        b[1] = (value >> 8) & 0xff;
        b[2] = (value >> 16) & 0xff;
        b[3] = (value >> 24) & 0xff;
    }
}