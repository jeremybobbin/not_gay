#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define MAX 100

int getop(char s[]) {
	int i, c;
	static char ch[MAX];
	static int chp = -1;

	while ((s[0] = c = ((chp >= 0) ? ch[chp--] : getch())) == ' ' || c == '\t');
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')
		return c;


	i = 0;

	if (c == '-' && !isdigit(s[++i] = c = ((chp >= 0) ? ch[chp--] : getch())))
	{
		ch[chp++] = c;
		return '-';
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = ((chp >= 0) ? ch[chp--] : getch())));

	if (c == '.')
		while (isdigit(s[++i] = c = ((chp >= 0) ? ch[chp--] : getch())));

	s[i] = '\0';
	if (c != EOF)
		ch[chp++] = c;

	return NUMBER;
}
