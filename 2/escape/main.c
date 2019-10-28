#include <stdio.h>
#include <time.h>

int escape(char s[], char t[]) {
	int i, j;
	char c;
	for (i = j = 0; s[i] != '\0'; i++) {  
		c = s[i];
		switch(c) {
			case '\n':
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case '\t':
				t[j++] = '\\';
				t[j++] = 't';
				break;
			default:
				t[j++] = c;
				break;
		}
	}

	t[j] = '\0';
	return j;
}

int unescape(char s[], char t[]) {
	int i, j;
	char c;
	for (i = j = 0; c != '\0'; c = s[i++])
		if (c == '\\')
			switch(s[i++]) {
				case 'n':
					t[j++] = '\n';
					break;
				case 't':
					t[j++] = '\t';
					break;
				default:
					t[j++] = '\\';
					t[j++] = s[i];
					break;
			}
		else
			t[j++] = c;

	t[j] = '\0';
	return j;
}

int main(int argc, char * argv) {
	char s[200];
	char t[200];
	int i = 0;
	int c;
	while ((c = getchar()) != EOF) {
		s[i++] = c;
	}
	s[i] = '\0';

	printf("Original: %s\n", s);
	escape(s, t);
	printf("Escaped: %s\n", t);
	unescape(t, s);
	printf("Unescaped: %s\n", s);
}
