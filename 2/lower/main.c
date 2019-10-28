#include <stdio.h>

unsigned lower(char c) {
	return c >= 'A' && c <= 'Z' ? (c - 'A') + 'a' : c;
}

int main(int argc, char * argv) {
	printf("%c\n", lower('T'));
	printf("%c\n", lower('a'));
	printf("%c\n", lower('1'));
}
