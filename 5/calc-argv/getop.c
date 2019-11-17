#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define MAX 100


int getop(char d[], char s[]) {
	while ((*d = *s++) == ' ' || *d == '\t');
	*(d+1) = '\0';

	if (!isdigit(*d) && *d != '.' && *d != '-')
		return *d;

	if (*d == '-' && !isdigit(*++d = *s++))
		return '-';

	if (isdigit(*d))
		while (isdigit(*++d = *s++));

	if (*d == '.')
		while (isdigit(*++d = *s++));

	*d = '\0';

	return NUMBER;
}
