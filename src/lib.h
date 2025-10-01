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

struct BlockChain;

struct BlockChain {
    Block b;
    struct BlockChain* prev;
};

Block create_block(const Block* prev_block, const Tx* tx);
Tx creates_tx(char* message);
Block create_genesis();

struct BlockChain add_block(struct BlockChain* chain, Block block);
Block* find_block(const struct BlockChain* chain, uint32_t height);

void print_block(const Block* block);

#endif