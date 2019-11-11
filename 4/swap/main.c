#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#define swap(t, x, y) t z = x; x = y; y = z

int main(int argc, char * argv) {
	int a = 1, b = 2;
	printf("Before, A: %d, B: %d\n", a, b);
	swap(int, a, b);
	printf("After, A: %d, B: %d\n", a, b);
}
