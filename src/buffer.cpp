#include "buffer.h"

namespace Buffer {
    uint32_t ReadUint32(const uint8_t *b) {
        return b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
    }
}