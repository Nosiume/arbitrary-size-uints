#include "bigint.h"

int main(int argc, char** argv) {
	bigint_t* a = uint_to_bg(2372283263);
	bigint_t* b = uint_to_bg(82278362);
	bigint_t* res = bg_sub(a, b);
	bg_printhex(res);
	return 0;
}
