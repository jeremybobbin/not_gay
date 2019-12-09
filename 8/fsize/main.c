#include <sys/resource.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 1024

int fsize(struct stat *stbuf) {
	return  stbuf->st_size;
}

int inode_no(struct stat *stbuf) {
	return  stbuf->st_ino;
}

int (*getter)(struct stat *) = fsize;

void dirwalk(char *dir, void (*fcn)(char *)) {
	char name [MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}

	while ((dp = readdir(dfd)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0
				|| strcmp(dp->d_name, "..") == 0)
			continue;
		if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name)) 
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
}


void recurstat(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, recurstat);

	printf("%81d %s\n", getter(&stbuf), name);
}


int main(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; i++) {
		if (*argv[i] == '-')
			switch (*(argv[i]+1)) {
				case 'i':
					getter = inode_no;
					argv++;
					argc--;
					break;
			}
	}


	if (argc == 1)
		recurstat(".");
	else
		while (--argc > 0)
			recurstat(*++argv);
	return 0;
}
