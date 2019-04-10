#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(int argc, char* argv[])
{
    int fd[argc];
   
    if(argc < 2) {
	fprintf(stderr, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
	printf("\t-a\tto open in append mode\n");
	printf("\t-f\tto truncate\n");
	exit(1);
    }
    
    
    /*if they want to use options*/
     
    if(argv[1][0] == '-') {
	switch(argv[1][1]) {
	    case 'a':
		printf("they used a, so open in append mode");
		break;
	    case 'f':
		printf("they used f, so use truncate option");
		break;
	    default:
		printf("invalid option\n");
		exit(1);
		}
	    }
    /*if not, just create the files, give them individual fd numbers */
    for(int i = 1; i < argc; i++) {
	fd[i] = open(argv[i], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR); 
	if(fd[i] == -1) perror("cannot open file");
    }

    char buf[BUFFER_SIZE];
    int bytes_read;

    while((bytes_read = read(STDIN_FILENO, buf, sizeof(buf)-1)) > 0) {
	/*set the last byte to null, this will ensure we won't get random characters*/
	buf[bytes_read] = 0x00;
	/*write to stdout*/
	printf("%s", buf);
	/*don't write the whole buffer, just write till null*/
	int nbytes = strlen(buf);
	for(int i = 1; i < argc; i++) write(fd[i], buf, nbytes);
    }
    
    /*after operation is done, close all files*/
    for(int i = 1; i < argc; i++) close(fd[i]);
     
    return 0;
}

