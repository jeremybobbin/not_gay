#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 80

int main(int argc, char *argv[])
{
	int c, linelen = 0;
	while ((c = getchar()) != EOF) {
		if (linelen > MAX_LINE_LEN) {
			linelen = 0;
			putchar('\n');
		}

		if (isgraph(c) || c == '\t' || c == ' ' || c == '\r') {
			putchar(c);
			linelen++;
		} else if (c == '\n') {
			linelen = 0;
			putchar(c);
		} else {
			linelen += printf(" 0x%X ", c);
		}
	}
}

