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

int strrindex(char s[], char t) {
	int i;
	int occ = -1;
	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == t)
			occ = i;

	return occ;
}


int main(int argc, char * argv) {
	printf("'l' in \"Poland\": %d\n", strrindex("Poland", 'l'));
	printf("'d' in \"Germany\": %d\n", strrindex("Germany", 'd'));
}
