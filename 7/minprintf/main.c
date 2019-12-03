#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'o':
				ival = va_arg(ap, int);
				printf("%o", ival);
				break;
			case 'x':
				ival = va_arg(ap, int);
				printf("%x", ival);
				break;
			case 'X':
				ival = va_arg(ap, int);
				printf("%X", ival);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}

int main(int argc, char *argv[])
{
	minprintf("%o\n", 63);
	minprintf("%x\n", 63);
	minprintf("%X\n", 63);
}

