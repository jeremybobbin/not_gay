#include <stdio.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXHEAP 5000000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int (*cmp_fn)(void *, void *);

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

int strcmp(char *s, char *t)
{
	int v;
	while ((v = (*s++ - *t++)) == 0 && *s != '\0' && *t != '\0');
	return v;
}

int isletter(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int isnum(char c)
{
	return c >= '0' && c <= '9';
}

int isblank(char c)
{
	return c == ' ';
}

int dircmp(char *s, char *t)
{
	int v = 0;
	while (*s != '\0' && *t != '\0')
	{
		if(!(isnum(*s) || isblank(*s) || isletter(*s)))
		{
			s++;
			continue;
		}
		if(!(isnum(*t) || isblank(*t) || isletter(*t)))
		{
			t++;
			continue;
		}
		if ((v = *s++ - *t++) != 0)
			break;
	}
	return v;
}


char tolower(char c) 
{
	if (c >= 'A' && c <= 'Z')
		c = (c - 'A') + 'a';

	return c;
}

int dir_char(char c)
{
	return isnum(c) || c == ' ' || isletter(c);
}

int dircmpi(char *s, char *t)
{
	int v = 0;
	while (*s != '\0' && *t != '\0')
	{
		while(!dir_char(*s))
			s++;

		while(!dir_char(*t))
			t++;

		if ((v = tolower(*s++) - tolower(*t++)) != 0)
			break;
	}
	return v;
}


int strcmpi(char *s, char *t)
{
	int v;
	while ((v = (tolower(*s++) - tolower(*t++))) == 0 && *s != '\0' && *t != '\0');
	return v;
}

int readlines(char *lineptr[], int maxlines, char *heap, int maxheap) {
	int len, nlines;
	char *heapstart = heap;
	char line[MAXLEN];

	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines /* || heap < (heap + maxheap) */ )
		{
			return -1;
		}
		else {
			line[len - 1] = '\0';
			strcpy(heap, line);
			lineptr[nlines++] = heap;
			heap += len;
		}
	return nlines;
}

int writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

int strlen(char *s)
{
	char *p;
	for (p = s; *p != '\0'; p++);
	return p - s;
}

int isspace(char c)
{
	return c == ' ' || c == '\n' || c == '\t';
}

int reverse(char s[]) {
	int i, j;
	char c;
	for (i = 0, j = (strlen(s) - 1); i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}


int rev(void *p1, void *p2)
{
	return -1 * cmp_fn(p1, p2);
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void jsort(void *v[], int left, int right,
		int (*comp)(void *, void *))
{
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	jsort(v, left, last-1, comp);
	jsort(v, last+1, right, comp);
}


int main(int argc, char *argv[]) {
	int i;
	int nlines;
	int numeric = 0, reverse = 0, fold = 0, directory;
	char heap[MAXHEAP];

	for (i = 1; i < argc; i++)
		if (*argv[i] == '-')
			switch (*(argv[i] + 1)) {
				case 'n':
					numeric = 1;
					break;
				case 'r':
					reverse = 1;
					break;
				case 'f':
					fold = 1;
					break;
				case 'd':
					directory = 1;
					break;
				default:
					printf("Bad option: '%s'\n", argv[i]);
			}

	if (fold && numeric)
	{
		printf("Can't use -f with -n\n");
		return 1;
	}

	if (numeric)
		cmp_fn = numcmp;
	else if (directory && fold)
		cmp_fn = dircmpi;
	else if (fold)
		cmp_fn = strcmpi;
	else if (directory)
		cmp_fn = dircmp;
	else
		cmp_fn = strcmp;

	if ((nlines = readlines(lineptr, MAXLINES, heap, MAXHEAP)) >= 0) {
		jsort((void **) lineptr, 0, nlines-1,
				(int (*)(void*, void*)) (reverse ? rev : cmp_fn));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("Input too big to sort.\n");
		return 1;
	}
}
