#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

void strcat(char *s, char *t)
{
	while (*++s); // Goto '\0'
	while (*s++ = *t++);
}

// If t occurs at end of s
int strend(char *s, char *t)
{
	/* s start, t start */
	char *ss = s;
	char *ts = t;

	while(*++s);
	while(*++t);

	while (s > ss && t > ts && *--s == *--t);

	if (t == ts)
		return 1;
	else
		return 0;

}

int main(int argc, char * argv) {
	char s[] = "Hello, \0            ";
	char t[] = "guy!";

	strcat(s, t);

	printf("%s\n", s); // Hello, guy

	if (strend(s, t))
		printf("'%s' ends with '%s'\n", s, t);

	char u[] = "I wanna fuck you in the ass Saturday.";
	char v[] = "next wednesday instead.";
	if (!strend(u, v))
		printf("'%s' does not end with '%s'\n", u, v);

}
