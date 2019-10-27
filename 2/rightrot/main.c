#include <stdio.h>

int rightrot(unsigned x, int n) {
	unsigned right = ~(~0 << n) & x;
	// how to get rid of 32 without sizeof?
	return (right << 32 - n) | (x >> n);
}

int main(int argc, char * argv) {
	printf("%x\n", 0x000f);
	printf("%x\n", rightrot(0x000f, 4));
}
