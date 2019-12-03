#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void conv(int (*conv)(int)) {
	int c;
	while ((c = getchar()) != EOF)
		putchar(conv(c));
}

int main(int argc, char *argv[])
{
	int c;
	int (*fn)(int) = tolower;

	if (argc > 1)
		if (strcmp(argv[1], "upper") == 0)
			fn = toupper;
	conv(fn);
}

