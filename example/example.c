#include "bigint.h"
#include <stdio.h>

int main(int argc, char** argv) {
	bigint_t* a = uint_to_bg(1);
	bigint_t* b = bg_lshift(a, 128);
	bigint_t* res = bg_mul(a, b);

	// Print block data
	printf("0x");
	for(size_t i = 0 ; i < res->block_count ; i++) {
		printf("%x", res->blocks[i]);
	}
	putchar(0xa);
	return 0;
}
