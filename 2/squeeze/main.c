#include <stdio.h>

int jer_squeeze(char s1[], char s2[]) {
	int i, j, k;

	for (i = k = 0; s1[i] != '\0'; i++) {

		int good = 1;

		for (j = 0; s2[j] != '\0'; j++)
			if (s1[i] == s2[j])
				good = 0;

		putchar(s1[i]);
		putchar('\n');

		if (good == 1)
			// segfaults with gcc, must be compiled wit tcc D:<
			s1[k++] = s1[i];

	}

	s1[k] = '\0';
}

int main(int argc, char * argv) {
	//for (int i = 1; (i + 1) < argc; i += 2) {
	jer_squeeze("lleleeelldke", "a");
		//printf("%s\n", argv[i]);
	//}
}
