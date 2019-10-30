#include <stdio.h>

int within(char c, char from, char to) {
	return c >= from && c <= to;
}

int contiguous(char from, char to) {
	return within(from, 'a', 'z') && within(to, 'a', 'z') ||
		within(from, 'A', 'Z') && within(to, 'A', 'Z') ||
		within(from, '0', '9') && within(to, '0', '9');
}

int expand(char s1[], char s2[]) {
	int i, j;
	char begin, end;
	for (i = j = 0; s1[i] != '\0'; i++) {
		if (s1[i + 1] == '-' && (end = s1[i + 2]) != '\0' && contiguous(begin = s1[i], end))
			for (i += 2; begin <= end; begin++)
				s2[j++] = begin;
		else
			s2[j++] = s1[i];
	}

	s2[j] = '\0';
	return j;
}

int main(int argc, char * argv) {

	char s1[] = " -a j-l- \n0-9a-z\nA-Za-z\na-Z";
	char s2[200] = "";

	expand(s1, s2);
	printf("%s\n", s2);

}
