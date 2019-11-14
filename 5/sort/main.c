#include <stdio.h>

#define MAXLINES 5000
#define MAXHEAP 5000000
#define MAXLEN 1000

char *lineptr[MAXLINES];

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

int readlines(char *lineptr[], int maxlines, char *heap, int maxheap) {
	int len, nlines;
	char *heapstart = heap;
	char line[MAXLEN];

	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0)
		if (nlines >= maxlines /* || heap < (heap + maxheap) */ )
		{
			printf("Heap - Start: %d\n", heap - heapstart);
			printf("Nlines: %d\n", nlines);
			return -1;
		}
		else {
			line[len - 1] = '\0';
			strcpy(heap += len, line);
			lineptr[nlines++] = heap;
		}
	return nlines;
}

int writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void qsort(char *v[], int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);

	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

int main(int argc, char * argv) {
	int nlines;
	char heap[MAXHEAP];

	if ((nlines = readlines(lineptr, MAXLINES, heap, MAXHEAP)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("Input too big to sort.\n");
		return 1;
	}
}
