#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <locale.h>
#include <langinfo.h>

int main(int argc, char *argv[]){
	if(argc != 2) {
		printf("The program needs one arguments: path of the directory.\n");
		exit(1);
	}
	struct dirent *pDirent;
	struct stat statbuf;
	DIR *pDir;
	pDir = opendir (argv[1]);
	if (pDir == NULL) {
        	printf ("Cannot open directory '%s'\n", argv[1]);
        	return 1;
    	}
	while ((pDirent = readdir(pDir)) != NULL) {
		if (stat(pDirent->d_name, &statbuf) == -1)
			continue;
	        printf ("%s		", pDirent->d_name);
		printf("%9jd\n", (intmax_t)statbuf.st_size);
	}
	closedir (pDir);
	return 0;
}
