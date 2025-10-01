#include "lib.h"

Block create_block(Block prev_block, Tx tx) {
    Block new_block;
    new_block.height = prev_block.height + 1;
    new_block.timestamp = 0;
    new_block.tx = tx;
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