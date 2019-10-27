#include <stdio.h>

unsigned setbits(unsigned x, unsigned y, int p, int n) {
	unsigned mask = ~(~0 << n) & y;
	x ^= ~(~0 << n) << p;
	x |= (mask << p);
	return x;
}

int main(int argc, char * argv) {
	unsigned mask = setbits(0x0f00, 0xffff, 0, 4);

	printf("%x\n", 0xf0f0);
	printf("%x\n", mask);
}
