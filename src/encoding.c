#include <stdlib.h>
#include "encoding.h"

size_t bytes_len(const Tx* tx) {
    return (4 + strlen(prev_block.tx.message)) * sizeof(uint8_t);
}

void to_le_bytes(uint32_t v, uint8_t* buf) {
    buf[0] = (uint8_t)(v & 0xFF);
    buf[1] = (uint8_t)((v >> 8) & 0xFF);
    buf[2] = (uint8_t)((v >> 16) & 0xFF);
    buf[3] = (uint8_t)((v >> 24) & 0xFF);
}

void to_le_bytes(uint16_t v, uint8_t* buf) {
    buf[0] = (uint8_t)(v & 0xFF);
    buf[1] = (uint8_t)((v >> 8) & 0xFF);
}

void to_bytes(const Tx* tx, uint8_t* buf) {
    memcpy(buf, tx.message, strlen(tx.message))
    to_le_bytes(tx.timestamp, buf + strlen(tx.message))
}