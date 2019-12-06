#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

int ch = -1;
int getch()
{
	char c = ch == -1 ? getchar() : ch;
	ch = -1;
	return c;
}

void ungetch(int c)
{
	ch = c;
}

int minscanf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval, c;
	int *ival, i;
	double *dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			if (*p == (c = getch()))
				continue;
			else {
				ungetch(c);
				break;
			}
		}
		switch (*++p) {
			case 'd':
				ival = va_arg(ap, int *);
				printf("a\n");
				scanf("%d", ival);
				printf("b\n");
				break;
			case 'f':
				dval = va_arg(ap, double*);
				scanf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'o':
				ival = va_arg(ap, int*);
				scanf("%o", ival);
				break;
			case 'x':
				ival = va_arg(ap, int*);
				scanf("%x", ival);
				break;
			case 'X':
				ival = va_arg(ap, int*);
				scanf("%X", ival);
				break;
			default:
				if (*p == (c = getch()))
					continue;
				else {
					ungetch(c);
					break;
				}
				break;
		}
		i++;
	}
	va_end(ap);
	return i;
}

int main(int argc, char *argv[])
{
	int i;
	minscanf("%d", &i);
	printf("Got: %d\n", i);
}

