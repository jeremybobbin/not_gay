#include <stdio.h>

#define MAX_LEN 30
#define OFFSET 20

int get_line(char line[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		line[i] = c;

	if (c == '\n') {
		line[i] = c;
		i++;
	}

	line[i] = '\0';
	return i;
}

int main() {
	int len, i;
	char line[MAX_LEN];
	while ((len = get_line(line, MAX_LEN)) > 0) {
		if (len == MAX_LEN - 1 && line[MAX_LEN - 2] != '\n') {
			for (i = MAX_LEN - 2; i > (MAX_LEN - OFFSET); i--) {
				if(line[i] == ' ' || line[i] == '\t' || line[i] == '\b') {
					line[i] = '\n';
					printf(line);
					break;
				}
			}
			if (i == (MAX_LEN - OFFSET)) {
				printf("%s-\n", line);
			}

		} else {
			printf("%s", line);
		}
	}
}
