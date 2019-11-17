#include <stdio.h>
#include <stdlib.h>

#define SPACES 4
#define DEFAULT_SPACES 4
#define LIST_MAX 100
#define MIN(a, b) a < b ? a : b


int parse(int *spaces, int lim, int argc, char *argv[], int *n, int *m)
{
	int i, j;
	j = 0;
	if (argc > 1)
		for (i = 1; i < argc; i++)
			if (isdigit(*argv[i]))
				spaces[j++] = atoi(argv[i]);
			else if (*argv[i] == '-') {
				switch(*(argv[i] + 1)) {
					case 'm':
						*m = atoi(argv[++i]);
						break;
					case 'n':
						*n = atoi(argv[++i]);
						break;
					default:
						printf("Unknown argument: %s\n", argv[i]);
				}
			}

	else
		spaces[j++] = DEFAULT_SPACES;

	return j;
}

int main(int argc, char *argv[]) {
	int c, i, j, spaces[LIST_MAX], len, n, m, col;
	c = i = j = 0;
	n = -1;
	m = 0;

	argc = MIN(argc, LIST_MAX);
	len = parse(spaces, LIST_MAX, argc, argv, &n, &m);

	col = 0;
	while (1) {
		c = getchar();
		if (n != -1 && (col - m) > 0 && ((col - m) % n) == 0)
			putchar('\t');
		col++;
		if (c == ' ') {
			if (++i == spaces[j]) {
				if (++j == len)
					j = 0;
				putchar('\t');
				i = 0;
			}
			continue;
		}

		if (c == '\n')
			col = 0;

		while (i > 0) {
			putchar(' ');
			i--;
		}

		if (c == EOF)
			break;

		putchar(c);
	}
}

