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

int itob(int n, int b, char s[]) {
	int i, sign;
	char c;

	sign = (n >= 0);

	i = 0;
	do {
		c = (n % b) + '0';

		/* shift from 0-9 to a-z if >9 */
		if (c > '9')
			c = (c - ('9' + 1)) + 'a'; 

		s[i++] = c;
	} while ((n /= b) > 0);

	if (sign)
		s[i++] = '\0';

	reverse(s);
}


int main(int argc, char * argv) {
	char s[50];

	/* 111 */
	itob(256 + 16 + 1, 16, s);

	/* ff */
	itob(255, 16, s);

	printf("%s\n", s);

	return 0;
}
