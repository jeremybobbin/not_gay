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

int strncpy(char *s, char *ct, int n)
{
	char *end = ct + n;
	while (ct < end && (*s++ = *ct++) != '\0');
	return s;
}

int strncat(char *s, char *t, int n)
{
	char *ret = s;
	char *end = t + n;
	while (*++s); /* Goto '\0' */
	while (t < end && (*s++ = *t++));
	*s = '\0';
	return ret;
}

int strncmp(char *s, char *t, int n)
{
	while (n-- > 0 && *s && *t && *s++ == *t++);
	return *s - *t;
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

	char w[] = "I went in the store.";
	char x[] = "to a place.";
	strncpy(w + 7, x, 2);

	printf("%s\n", w);

	*(u + 28) = '\0';
	strncat(u, v, 14);
	printf("%s\n", u);
	
	if (strncmp("Apple", "Pear", 2) == ('p' - 'e'))
		printf("Strncmp!\n");
}
