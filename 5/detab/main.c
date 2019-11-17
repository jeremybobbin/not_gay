#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SPACES 4
#define LIST_MAX 100
#define MIN(a, b) a < b ? a : b


int parse(int *spaces, int lim, int argc, char *argv[])
{
	int i;
	if (argc > 1)
		for (i = 1; i < argc; i++)
			spaces[i - 1] = atoi(argv[i]);
	else
		spaces[0] = DEFAULT_SPACES;

	return argc - 1;
}

int main(int argc, char *argv[]) {
	int c, i, j, spaces[LIST_MAX], len;
	argc = MIN(argc, LIST_MAX);
	
	len = parse(spaces, LIST_MAX, argc, argv);

	j = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (i = spaces[j]; i > 0; i--)
				putchar(' ');
			if (++j == len)
				j = 0;
		} else
			putchar(c);
	}
}
