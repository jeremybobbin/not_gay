#include <stdio.h>

unsigned bitcount(unsigned x) {
	int i;
	for (i = 0; x != 0; i++)
		x &= x - 1;

	return i;
}

int main(int argc, char * argv) {
	printf("%d\n", bitcount(0xf));
}
