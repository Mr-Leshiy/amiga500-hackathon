#ifndef ENCODING_H_INCLUDED
#define ENCODING_H_INCLUDED

#include <string.h>
#include <stdint.h>
#include "lib.h"


void to_le_bytes(uint32_t v, uint8_t* buf);

uint32_t tx_bytes_len(const Tx* tx);
uint32_t block_bytes_len(const Block* block);

void tx_to_bytes(const Tx* tx, uint8_t* buf);
Tx tx_from_bytes(uint8_t* buf);
void block_to_bytes(const Block* block, uint8_t* buf);

#endif