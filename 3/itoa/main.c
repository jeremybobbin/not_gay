#include <stdio.h>
#include <limits.h>

int strlen(char s[]) {
	int i = 0;
	while (s[++i] != '\0');
	return i;
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

int itoa(int n, char s[]) {
	int i, sign;
	char c;

	i = 0;
	if ((sign = n) < 0)
		do
			s[i++] =(-1 * (n % 10)) + '0';
		while((n /= 10) < 0);
	else
		do
			s[i++] = (n % 10) + '0';
		while((n /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}


int main(int argc, char * argv) {
	char s[] = "sleedle       ";
	itoa(INT_MIN, s);
	printf("%s\n", s);
}
