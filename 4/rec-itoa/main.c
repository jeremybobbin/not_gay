#include <stdio.h>
#include <limits.h>

int rec_itoa(char s[], int n) {
	int p = 0;
	if (n < 0)
	{
		s[0] = '-';
		s += 1;
		n = -n;
	}

	if (n / 10)
		p = rec_itoa(s, n / 10);
	else
		s[p + 1] = '\0'; // GCC can't seem to handle this

	s[p] = (n % 10) + '0';
	return p + 1;
}

int main(int argc, char * argv) {
	char s[100];
	rec_itoa(s, -123456789);
	printf("Result 50: '%s'\n", s);
	return 0;
}
