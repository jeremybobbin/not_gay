#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 500


int printfile(char *name, int rows, int cols) {
	FILE *fp;
	int r, c;
	char ch;

	if ((fp = fopen(name, "r")) == NULL)
		return 0;
	
	for (;;) {
		printf("%s\n\n", name);
		for (r = 1; r <= rows; r++) {
			for (c = printf("%d ", r); c < cols; ) {
				if ((ch = fgetc(fp)) == EOF)
				{
					while (r++ < rows)
						putchar('\n');
					return 0;
				}

				if(ch == '\n')
					break;

				if(ch == '\t')
					c+=8;
				else c++;


				putchar(ch);
			}
			putchar('\n');
		}
		putchar('\n');
		putchar('\n');
	}
}

/* Outdated excersize... */

int main(int argc, char *argv[])
{
	int i;

	if (argc < 2) {
		fprintf(stderr, "%s requires at least 1 argument\n", argv[0]);
		exit(1);
	}
	for (i = 1; i < argc; i++)
		printfile(argv[i], 40, 40);

}

