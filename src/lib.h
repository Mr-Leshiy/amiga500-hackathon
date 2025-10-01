#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <stdint.h>

typedef struct {
    char* message;
    uint32_t timestamp;
} Tx;

typedef struct {
    // uint8_t[32] prev_hash;
    uint16_t height;
    uint32_t timestamp;
    Tx tx;
} Block;

Block create_block(Block prev_block, Tx tx);
Tx creates_tx(char* message);
Block create_genesis();

#endif