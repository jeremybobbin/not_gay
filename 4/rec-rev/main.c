#include <stdio.h>
#include <limits.h>

int __rec_rev(char s[], int i, int j) {
	char c;
	if (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		__rec_rev(s, i + 1, j - 1);
	}
}

int rec_rev(char s[]) {
	int j;
	while (s[++j] != '\0');
	__rec_rev(s, 0, j - 1);
}

int main(int argc, char * argv) {
	char s[] = "Jeremy";
	rec_rev(s);
	printf("Result: '%s'\n", s);
	return 0;
}
