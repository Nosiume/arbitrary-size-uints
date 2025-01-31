#include "bigint.h"

int main(int argc, char** argv) {
	bigint_t* a = uint_to_bg(12);
	bigint_t* b = uint_to_bg(8);
	bigint_t* res = bg_sub(a, b);
	bg_printhex(res);
	return 0;
}
