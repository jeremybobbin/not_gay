#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

void strcat(char *s, char *t)
{
	while (*++s); // Goto '\0'
	while (*s++ = *t++);
}

int main(int argc, char * argv) {
	char s[] = "Hello, \0            ";
	char t[] = "guy!";

	strcat(s, t);

	printf("%s\n", s); // Hello, guy



}
