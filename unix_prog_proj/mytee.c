#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    int fd;
   
    if (argc < 2) {
	fprintf(stderr, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
	printf("\t-a\tto open in append mode\n");
	printf("\t-f\tto truncate\n");
	exit(1);
    }
    
    /*
     * if they want to use options
     */
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
    /*
     * if not, just create normally
     */
    for(int i = 1; i < argc; i++) {
	fd = open(argv[i], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR); 
	    if(fd == -1) {
		perror("There is error");
		exit(1);
	        }
	/*
	 * reading/writing from stdin
	 */
        char *buffer = (char *)malloc(700*sizeof(char));
	read(STDIN_FILENO, buffer, 700);
	write(fd, buffer, 700);
	write(STDOUT_FILENO, buffer, 700);
    }

}
