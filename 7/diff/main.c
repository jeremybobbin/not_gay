#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int fgetline(char *line, FILE* fp, int max) {
	if (fgets(line, max, fp) == NULL)
		return 0;
	else
		return strlen(line);
}

#define MAX_FP 10
#define MAX_LINE 500

int main(int argc, char *argv[])
{

	int i, n, cmp, len, line;
	char curr[MAX_LINE], prev[MAX_LINE];
	FILE *iops[MAX_FP];

	if (argc < 3) {
		fprintf(stderr, "%s requires at least 2 arguments. Dang.\n", argv[0]);
		exit(1);
	}

	for (i = 1; (i < argc) && (i-1 < MAX_FP); i++)
		if ((iops[i-1] = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "%s couldn't open file: '%s'\n", argv[0], *argv);
			exit(1);
		}

	n = i - 1;

	for (line = 0; 1; line++)
		for (i = 0; i < n; i++) {
			if (fgetline(curr, iops[i], MAX_LINE) == 0) {
				fclose(iops[i]);
				iops[i] = NULL;
			}
			if (i != 0) {
				if (strcmp(curr, prev) != 0) {
					printf("%s, line %d: %s", argv[i+1], line, curr);
					printf("%s, line %d: %s", argv[i], line, prev);
					exit(0);
				} else if (iops[i] != NULL && iops[i-1] == NULL) {
					printf("file '%s' ended prematurely", argv[i], line, curr);
					exit(0);
				} else if (iops[i] == NULL && iops[i-1] != NULL) {
					printf("file '%s' ended prematurely\n", argv[i+1], line, curr);
					exit(0);
				}
			}
			strcpy(prev, curr);
		}
}

