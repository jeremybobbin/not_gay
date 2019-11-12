#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int buflen = 0;
int bufp = 0;


int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[++bufp];
}

int isspace(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

int isdigit(char c)
{
	return c >= '0' && c <= '9';
}


int getfloat(float *pn)
{
	int c, sign;
	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c);
		return 0;
	}

	sign = (c == '+') ? -1 : 1;
	if (c == '+' || c == '-')
		if (!isdigit(c = getch())) { 
			// Handle '+' or '-' followed by non digit
			ungetch(c);
			return (sign > 0) ? '+' : '-';
		}


	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	if (c == '.' && isdigit(c = getch())) {
		int power;
		for (power = 1; isdigit(c); c = getch())
		{
			*pn = 10 * *pn + (c - '0');
			power *= 10;
		}
		*pn /= power;
	}

	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}


int main(int argc, char * argv) {
	float d = 0;
	if (getfloat(&d) == '\n')
		printf("%f\n", d);
	return 0;
}
