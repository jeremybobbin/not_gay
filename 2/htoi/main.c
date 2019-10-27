#include <stdio.h>

int power(int base, int e) {
	int ret = 1;
	while(e > 0) {
		ret *= base;
		e--;
	}
	return ret;
}

int my_htoi(char s[]) {
	int total = 0;

	if (s[0] == '0' && s[1] == 'x' || s[1] == 'X')
		s = &s[2];

	int i;
	for (i = 0; s[i] != '\0'; i++) 
		if (s[i] >= 'A' && s[i] <= 'F')
			s[i] = (s[i] - 'A') + 'a';

	int len = i;
	int place = 0;

	for (i = len - 1; i >= 0; i--) {
		place = len - (i + 1);
		if (s[i] >= '0' && s[i] <= '9')
			total += power(16, place) * (s[i] - '0');
		else if (s[i] >= 'a' && s[i] <= 'f')
			total += power(16, place) * ((s[i] - 'a') + 10);
		else
			return -1;
	}

	return total;
}

int main(int argc, char * argv[]) {
		for (int i = 1; i < argc; i++) {
			printf("%d", my_htoi(argv[i]));
			if (i < (argc - 1))
				putchar(' ');
			else
				putchar('\n');
		}
}

