#include <stdio.h>

#define SPACES 4

int main() {
	int c, i = 0;
	while (1) {
		c = getchar();
		if (c == ' ') {
			if (++i == SPACES) {
				putchar('\t');
				i = 0;
			}
			continue;
		}

		while (i > 0) {
			putchar(' ');
			i--;
		}

		if (c == EOF)
			break;

		putchar(c);
	}
}

