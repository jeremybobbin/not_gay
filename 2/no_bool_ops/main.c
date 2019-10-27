#include <stdio.h>

#define LIMIT 80 

int getchar_lim(int got, int lim) {
	char c;

	if (got > LIMIT - 1)
		return -1;

	if ((c = getchar()) == '\n')
		return -1;
	else if (c == EOF)
		return -1;
	else
		return c;
}

int main() {
	int c;
	for (int i = 0; (c = getchar_lim(i, LIMIT)) != -1; i++)
		putchar(c);
}

