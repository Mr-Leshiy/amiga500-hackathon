#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"
#include "hashing/sha256.h"

Block create_block(Block prev_block, Tx tx) {
    Block new_block;
    new_block.height = prev_block.height + 1;
    new_block.timestamp = 0;
    new_block.tx = tx;

    // uint8_t* bytes = (uint8_t*) malloc(bytes_len(&tx));
    // to_bytes(&tx, bytes);
    // printf("%s", (char*) bytes);

    return new_block;
}

Block create_genesis() {
    Tx tx;
    tx.timestamp = 0;
    tx.message = "Hiiiiiiii !!!!!";

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

void print_block(const Block* block) {
    printf("height: %d, block_timestamp: %d, tx_message: %s, tx_timestamp: %d \n",
        block->height,
        block->timestamp,
        block->tx.message,
        block->tx.timestamp
    );
}