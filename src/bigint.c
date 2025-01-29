#include "bigint.h"

#define MAX(a,b) (((a) < (b)) ? (b):(a))
#define MIN(a,b) (((a) < (b)) ? (a):(b))
#define BG_MIN(a,b) (((a)->block_count < (b)->block_count) ? (b):(a))
#define BG_MAX(a,b) (((a)->block_count < (b)->block_count) ? (a):(b))

bigint_t* zero_nbits(unsigned int bits) {
	bigint_t* alloc = malloc(sizeof(bigint_t));
	if(alloc == NULL) return NULL;

	alloc->block_count = bits / 32 + 1;
	alloc->blocks = calloc(alloc->block_count, sizeof(unsigned int));
	return alloc;
}

bigint_t* uint_to_bg(unsigned int value) {
	bigint_t* alloc = malloc(sizeof(bigint_t));
	if(alloc == NULL) return NULL; // avoid NPE if we get memory issues

	alloc->block_count = 1;
	alloc->blocks = malloc(sizeof(int));
	alloc->blocks[0] = value;
	return alloc;
}

bigint_t* str_to_bg(char* string) {
	return NULL;	
}

void bg_delete(bigint_t* ptr) {
	free(ptr->blocks);
	free(ptr);
}

// Calculations

bigint_t* bg_add(bigint_t* lvalue, bigint_t* rvalue) {
	bigint_t* result = malloc(sizeof(bigint_t));

	size_t biggest_blcount = MAX(lvalue->block_count, rvalue->block_count);
	result->block_count = biggest_blcount + 1;
	result->blocks = calloc(result->block_count, sizeof(unsigned int));

	// Calculate resulting operation
	unsigned char carry = 0;
	size_t bit_index = 0;
	while (carry || bit_index < biggest_blcount * 32) {
		size_t bi = bit_index % 32;
		size_t i = bit_index / 32;

		unsigned int inbounds = i < biggest_blcount;
		unsigned char lbit = inbounds ? (lvalue->blocks[i] & (0x1 << bi)) > 0 : 0;
		unsigned char rbit = inbounds ? (rvalue->blocks[i] & (0x1 << bi)) > 0 : 0;
		unsigned char res = lbit ^ rbit ^ carry;

		//Full adder output
		result->blocks[i] |= (res << bi);
		carry = (lbit & rbit) + (carry & (lbit ^ rbit));

		bit_index++;
	}

	return result;
}


bigint_t* bg_sub(bigint_t* lvalue, bigint_t* rvalue) {
	return NULL;
}


bigint_t* bg_mul(bigint_t* lvalue, bigint_t* rvalue) {
	bigint_t* multiplicand = BG_MAX(lvalue, rvalue);
	bigint_t* multiplier = (multiplicand == lvalue) ? rvalue : lvalue; 
	// We calculate with multiplier as smallest number for optimizations
	
	size_t res_size = multiplicand->block_count + multiplier->block_count;
	bigint_t* res = malloc(sizeof(bigint_t));
	res->block_count = res_size;
	res->blocks = calloc(res->block_count, sizeof(unsigned int));

	for(size_t i = 0 ; i < multiplier->block_count ; i++) {
		for(size_t bi = 0 ; bi < 32 ; bi++) {
			if(!(multiplier->blocks[i] & (1 << bi))) continue; 

			bigint_t* shifted = bg_lshift(multiplicand, i*32 + bi);
			bigint_t* tmp = bg_add(res, shifted);

			bg_delete(res);
			bg_delete(shifted);
			res = tmp;
		}
	}

	return res;
}


bigint_t* bg_div(bigint_t* lvalue, bigint_t* rvalue) {
	return NULL;
}

bigint_t* bg_lshift(bigint_t* value, size_t offset) {
	bigint_t* res = malloc(sizeof(bigint_t));
	res->block_count = value->block_count + (offset / 32);
	res->blocks = calloc(res->block_count, sizeof(unsigned int));

	size_t bit_index = offset % 32;
	size_t blk_index = offset / 32;
	for(size_t i = 0 ; i < res->block_count ; i++) {
		for(size_t bi = 0 ; bi < 32 ; bi++) {
			size_t curr_bit_index = bi + bit_index % 32;
			size_t curr_blk_index = i + blk_index + (bi + bit_index) / 32;

			unsigned char bit = (value->blocks[i] & (1 << bi)) > 0;
			res->blocks[curr_blk_index] |= bit << curr_bit_index;
		}
	}
	return res;
}
