#include <stdio.h>
#include "calc.h"

char buf[BUFSIZE];
int buflen = 0;
int bufp = 0;

int get_line(char s[], int n)
{
	int i;
	char c;
	for (i = 0; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;

	if (c == '\n')
		s[++i] = '\n';

	s[i] = '\0';

	return i;

}



int strlen(char s[]) {
	int i;
	for (i = 0; s[i] != '\0'; i++);
	return i + 1;
}


int getch(void)
{
	if (bufp < buflen) {
		char c = buf[bufp++];
		return c;
	} else {
		if (get_line(buf, BUFSIZE) == 0)
			return EOF;

		buflen = strlen(buf);
		bufp = 0;
		return getch();
	}
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		bufp--;
}



void ungets(char s[]) {
	char c;
	int i;
	for (c = s[i = 0]; c != '\0'; c = s[i++])
		ungetch(s[i]);
}
