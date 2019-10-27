#include <stdio.h>

int jer_invert(unsigned x, int n, int p) {
	return x ^ (~(~0 << p) << n);
}

int main(int argc, char * argv) {
	printf("%x", jer_invert(0x0f0f0, 8, 4));
}
