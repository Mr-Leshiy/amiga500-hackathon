#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <stdint.h>

typedef struct {
    char* message;
    uint32_t timestamp;
} Tx;

typedef struct {
    char prev_hash_hex[65];
    uint32_t height;
    uint32_t timestamp;
    Tx tx;
} Block;

Block create_block(const Block* prev_block, const Tx* tx);
Tx creates_tx(char* message);
Block create_genesis();

void print_block(const Block* block);

#endif