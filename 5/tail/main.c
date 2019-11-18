#include <stdio.h>
#include <stdlib.h>

#define ALLOC_MAX 10000
#define LINE_LEN_MAX 100
#define MAX_LINES 100
#define MAX(a, b) a > b ? a : b

char alloc_buf[ALLOC_MAX];
int allocp; /* entry num */

char *alloc(int size)
{
	char *ret;
	if (alloc_buf + (ALLOC_MAX - allocp) < size) 
		return 0;

	ret = &alloc_buf[allocp];
	allocp += size;
	return ret;
}

int get_line(char *s, int maxlen)
{
	int c;
	char *b = s;
	while (maxlen-- > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;

	if (c == '\n')
		*s++ = '\n';

	*s = '\0';

	return s - b;
}

int strcpy(char *s, char *t)
{
	while (*s++ = *t++);
}

/* Does not use optimal amount of memory */
int main(int argc, char *argv[]) {
	int len, n, i, print;
	if (argc < 2) {
		print = 10;
	} else if ((print = atoi(argv[1])) < 0) {
		printf("Cannot parse '%s'.\n", argv[1]);
		return 1;
	}

		
	char s[LINE_LEN_MAX], *lines[MAX_LINES], *ptr;
	for (n = 0; (len = get_line(s, LINE_LEN_MAX)) > 0 && n < MAX_LINES; n++)
	{
		if (!(ptr = alloc(len + 2))) {
			printf("Could not alloc for string: '%s'\n", s);
			return 1;
		}
		strcpy(ptr, s);
		lines[n] = ptr;
	}
	for (i = ((n - print) < 0 ? 0 : n - print); i < n; i++){
		printf("%s", lines[i]);
	}
}
