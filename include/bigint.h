#pragma once

#include <stdlib.h>

typedef struct {
	unsigned int* blocks;
	size_t block_count;
} bigint_t;

bigint_t* zero_nbits(unsigned int bits);
bigint_t* uint_to_bg(unsigned int value);
bigint_t* str_to_bg(char* string); 
void bg_delete(bigint_t* ptr);

bigint_t* bg_add(bigint_t* lvalue, bigint_t* rvalue);
bigint_t* bg_sub(bigint_t* lvalue, bigint_t* rvalue);
bigint_t* bg_mul(bigint_t* lvalue, bigint_t* rvalue);
bigint_t* bg_div(bigint_t* lvalue, bigint_t* rvalue);

bigint_t* bg_lshift(bigint_t* value, size_t offset);
bigint_t* bg_rshift(bigint_t* value, size_t offset);

