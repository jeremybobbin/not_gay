#include <stdio.h>

#define NONE	0
#define QUOTE	1
#define COMMENT	2
#define PAREN	3
#define SQUARE	4
#define CURLY	5

#define OPENERS	"([{"
#define CLOSERS	")]}"

#define OK	0
#define ERR	-1

int idx;

int contains(char *hay, char needle) {
	for(int i = 0; hay[i] != '\0'; i++)
		if(hay[i] == needle)
			return i;
	return -1;
}


int valid(int state, char openers[], char closers[]) {
	char c;
	int i;
	while ((c = getchar()) != EOF) {
		idx++;
		if ((i = contains(openers, c)) != -1)
			if (printf("index: %d\n", idx) && valid(i, openers, closers) == ERR) {
				
				return ERR;
			}

		if (state == NONE || (i = contains(closers, c)) != -1)
			return OK;
	}
}

int main() {
	return valid(NONE, OPENERS, CLOSERS);
}

