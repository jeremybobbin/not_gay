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

int itoa_pad(int n, char s[], int m) {
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

	while (i < m)
		s[i++] = ' ';

	s[i] = '\0';
	reverse(s);
}


int main(int argc, char * argv) {
	char a[50];
	char b[50];
	char c[50];
	char d[50];
	char e[50];
	itoa_pad(5000000000, a, 8);
	itoa_pad(628, b, 8);
	itoa_pad(1, c, 8);
	itoa_pad(9001, d, 8);
	itoa_pad(200, e, 8);
	printf("%s %s %s %s %s\n", a, b, c, d, e);
}
