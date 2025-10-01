#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"
#include "hashing/sha256.h"
#include "encoding.h"

Block create_block(const Block* prev_block, const Tx* tx) {
    Block new_block;
    new_block.height = prev_block->height + 1;
    new_block.timestamp = 0;
    new_block.tx = *tx;

    uint32_t bytes_size = block_bytes_len(prev_block);
    uint8_t* bytes = (uint8_t*) malloc(bytes_size);
    block_to_bytes(prev_block, bytes);
    sha256_easy_hash_hex(bytes, sizeof(bytes), new_block.prev_hash_hex);

    return new_block;
}

Block create_genesis() {
    Tx tx;
    tx.timestamp = 0;
    tx.message = "Genesis Block";

    Block genesis;
    genesis.height = 0;
    genesis.timestamp = 0;
    genesis.tx = tx;

    return genesis;
}

Tx creates_tx(char* message) {
    Tx tx;
    tx.timestamp = 0;
    tx.message = message;
    return tx;
}

struct BlockChain add_block(struct BlockChain* chain, Block block) {
    // struct BlockChain* new_head = (struct BlockChain *) malloc(sizeof(struct BlockChain));
    struct BlockChain new_head;
    new_head.b = block;
    new_head.prev = chain;

    print_block(&new_head.b);
    return new_head;
}

Block* find_block(const struct BlockChain* chain, uint32_t height) {
    const struct BlockChain* walk = chain;

    while(walk) {
        printf("%d\n", walk->b.height);
        if(walk->b.height == height) {
            return &walk->b;
        }
        walk = walk->prev;
    }

    return &chain->b;
}

void print_block(const Block* block) {
    printf("height: %d, block_timestamp: %d, tx_message: %s, tx_timestamp: %d, prev_hash: %s \n",
        block->height,
        block->timestamp,
        block->tx.message,
        block->tx.timestamp,
        block->prev_hash_hex,
    );
}