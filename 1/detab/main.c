#include <stdio.h>

#define SPACES 4

int main() {
	int c, i;
	while ((c = getchar()) != EOF) {
		if (c == '\t')
			for (i = SPACES; i > 0; i--)
				putchar(' ');
		else
			putchar(c);
	}
}
