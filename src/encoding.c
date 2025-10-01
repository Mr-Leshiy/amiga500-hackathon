#include <stdlib.h>
#include <stdint.h>
#include "encoding.h"
#include "lib.h"

uint32_t tx_bytes_len(const Tx* tx) {
    return (4 + strlen(tx->message)) * sizeof(uint8_t);
}

uint32_t block_bytes_len(const Block* block) {
    // hash hex + height + timestamp + tx
    return (65 + 4 + 4 + tx_bytes_len(&block->tx));
}

void to_le_bytes(uint32_t v, uint8_t* buf) {
    buf[0] = (uint8_t)(v & 0xFF);
    buf[1] = (uint8_t)((v >> 8) & 0xFF);
    buf[2] = (uint8_t)((v >> 16) & 0xFF);
    buf[3] = (uint8_t)((v >> 24) & 0xFF);
}

void tx_to_bytes(const Tx* tx, uint8_t* buf) {
    to_le_bytes(tx->timestamp, buf);
    strcpy(buf + 4, tx->message);
}

Tx tx_from_bytes(uint8_t* buf) {
    Tx tx;
    tx.message = buf + 4;
    tx.timestamp = ((uint32_t) buf[0]) + ((uint32_t) buf[1]) << 8 + ((uint32_t) buf[2]) << 16 + ((uint32_t) buf[3]) << 24;
    return tx;
}

void block_to_bytes(const Block* block, uint8_t* buf) {
    size_t offset = 0;
    memcpy(buf, block->prev_hash_hex, strlen(block->prev_hash_hex));
    offset += strlen(block->prev_hash_hex);
    to_le_bytes(block->height, buf + offset);
    offset += 4;
    to_le_bytes(block->timestamp, buf + offset);
    offset += 4;
    tx_to_bytes(&block->tx, buf + offset);
}