#include <stdio.h>
// Works with everything except unsigned int for some reason; 

int main() {
	char a, b, upper, lower;
	for (a = 2, b = 1; a > b; a = 2 * a) 
		b = a;

	upper = ((b - 1) * 2) + 1;
	lower = upper + 1;
	printf("Upper limit: %d\n", upper);
	printf("Lower limit: %d\n", lower);
}
