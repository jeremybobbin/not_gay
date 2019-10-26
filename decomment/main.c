#include <stdio.h>

#define NONE 0
#define QUOTE 1
#define COMMENT 2
#define LINE_COMMENT 3

/* Test Comment */
/* With "Quotes" */

/* 
 * On multiple lines
 */

int main() {
	char * test = "This is not a test /* */ ";
	char prev = 0;
	int curr, state = 0;
	int timeout = 0;

	while ((curr = getchar()) != EOF) {
		if (prev == '/' && curr == '*' && state == NONE)
			state = COMMENT;

		if (prev == '*' && curr == '/' && state == COMMENT) {
			state = NONE;
			timeout += 2;
		}

		if (prev != '\\' && curr == '"' && state == QUOTE)
			state = NONE;

		if (prev != '\\' && curr == '"' && state == NONE)
			state = QUOTE;

		if (prev == '/' && curr == '/' && state == NONE)
			state = LINE_COMMENT;

		if (curr == '\n' && state == LINE_COMMENT)
			state = NONE;

		if (state != LINE_COMMENT && state != COMMENT && ! timeout)
			putchar(prev);

		if (timeout)
			timeout--;

		prev = curr;
	}
	putchar(prev);
}
