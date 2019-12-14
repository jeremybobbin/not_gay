#include <unistd.h>
#include "fileops.h"
#include "malloc.h"


#define MAX_LEN 80

int get_line(char *sp, int lim) {
	char *s = sp, c;
	while ((c = getchar()) != EOF && --lim > 0 && c != '\n')
			*s++ = c;

	if (c == '\n')
		*s++ = c;

	*s ='\0';
	return s - sp;
}

void strcpy(char *d, char *s)
{
	while (*d++ = *s++);
}

int main(int argc, char *argv[])
{
	char s[MAX_LEN], *lines[MAX_LEN];
	int len, i;
	//for (i = 0; (len = get_line(s, MAX_LEN)) != 0 && i < MAX_LEN - 1; i++) {
	//	if ((lines[i] = (char *) malloc(len+10)) == NULL)
	//		putstr("error\n");
	//	else
	//		strcpy(lines[i], s);
	//}
	//lines[i] = NULL;

	//for (i = 0; lines[i]; i++)
	//	putstr(lines[i]);

	//_flushbuf(-1, stdout);

	char *ptr;
	if ((ptr = calloc(500, sizeof(int))) == NULL)
		putstr("FUCK\n");

	for (int i = 0; i < 500; i++)
		if ((char) *(ptr+i) == 0)
			putstr("WIN\n");
		else
			putstr("DANG\n");

	return 0;
}

