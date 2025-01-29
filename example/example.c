#include "bigint.h"
#include <stdio.h>

int main(int argc, char** argv) {
	bigint_t* a = uint_to_bg(2389237129);
    bigint_t* b = uint_to_bg(937237622);
    bigint_t* c = uint_to_bg(2031230123);
    bigint_t* d = bg_mul(a, c);
    bigint_t* res = bg_mul(b, d);

	// Print block data
    printf("0x");
	for(int i = res->block_count - 1 ; i >= 0 ; i--) {
		printf("%08x", res->blocks[i]);
	}
	putchar(0xa);
	return 0;
}
