#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 500

// needle: ababc
// haystack: abababc
int contains(char *haystack, char *needle) {
	char *h, *n;
	for (; *haystack; haystack++) {
		for (n = needle, h = haystack; *n && *n == *h; n++, h++);
		if (!*n)
			return 1;
	}
	return 0;
}

int fgetline(char *line, FILE* fp, int max) {
	if (fgets(line, max, fp) == NULL)
		return 0;
	else
		return strlen(line);
}

int gerpio(FILE *ifp, FILE *ofp, char *needle)
{
	char *s[MAX_LINE];
	while (fgetline(s, ifp, MAX_LINE) > 0)
		if(contains(s, needle))
			fputs(s, ofp);
}

int gerpio_fname(FILE *ifp, FILE *ofp, char *needle, char *fname)
{
	char *s[MAX_LINE];
	while (fgetline(s, ifp, MAX_LINE) > 0)
		if(contains(s, needle))
			fprintf(ofp, "%s:%s", fname, s);
}


int main(int argc, char *argv[])
{
	FILE *fp;
	if (argc < 2) {
		fprintf(stderr, "%s requires at least 1 argument\n", argv[0]);
	} else if (argc == 2) {
		gerpio(stdin, stdout, argv[1]);
	} else if (argc == 3) {
		if ((fp = fopen(argv[2], "r")) == NULL) {
			fprintf(stderr, "%s could not open file: %s\n", argv[0], argv[2]);
			exit(1);
		}
		gerpio(fp, stdout, argv[1]);
	} else {
		for (int i = 2; i < argc; i++) {
			if ((fp = fopen(argv[i], "r")) == NULL) {
				fprintf(stderr, "%s could not open file: %s\n", argv[0], argv[2]);
				exit(1);
			}
			gerpio_fname(fp, stdout, argv[1], argv[i]);
		}
	}
}

