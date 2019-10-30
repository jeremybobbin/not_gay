#include <stdio.h>

int expand(char s1[], char s2[]) {
	int i, j;
	char c;
	for (i = j = 0; s1[i] != '\0'; i++) {
		if (s1[i + 1] == '-' && s1[i + 2] != '\0' && s1[i] < s1[i + 2]) {
			for (c = s1[i]; c <= s1[i + 2]; c++)
				s2[j++] = c;
			i += 2;
		} else
			s2[j++] = s1[i];
	}

	s2[j] = '\0';
	return j;
}

int main(int argc, char * argv) {

	char s1[] = "0-9a-zA-Z";
	char s2[200] = "";

	expand(s1, s2);
	printf("%s\n", s2);

}
