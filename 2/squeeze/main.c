#include <stdio.h>

int jer_squeeze(char s1[], char s2[]) {
	int i, j, k;

	for (i = k = 0; s1[i] != '\0'; i++) {

		for (j = 0; s2[j] != '\0'; j++)
			if (s1[i] == s2[j])
				break;


		if (s2[j] == '\0')
			s1[k++] = s1[i];

	}

	s1[k] = '\0';
}

int main(int argc, char * argv) {
	char s[] = "lleleeelldke";
	jer_squeeze(s, "e");
	printf("%s\n", s);

}
