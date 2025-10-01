#ifndef ENCODING_H_INCLUDED
#define ENCODING_H_INCLUDED

#include <string.h>
#include <stdint.h>
#include "lib.h"

size_t bytes_len(const Tx* tx);
void to_le_bytes(uint32_t v, uint8_t* buf);
void to_le_bytes(uint16_t v, uint8_t* buf);
void to_bytes(const Tx* tx, uint8_t* buf);

#endif