#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define MAX_ARG 20

int main(int argc, char* argv[])
{
    int fd[MAX_ARG];
   
    if(argc < 2) {
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
     * if not, just create the files, give them individual fd numbers
     */
    for(int i = 1; i < argc; i++) {
	fd[i] = open(argv[i], O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR); 
	if(fd[i] == -1) perror("cannot open file");
    }

    char buf[2048];
    int bytes_read;
    while((bytes_read = read(STDIN_FILENO, buf, sizeof(buf)-1)) > 0) {
    write(STDIN_FILENO,buf, sizeof(buf)-1);
    }
    
    /*writing to file*/
    for(int i = 1; i < argc; i++) write(fd[i],buf, sizeof(buf)-1);
    
    /*stdout*/
    printf("\n%s\n", buf);
	
    for(int i = 1; i < sizeof(fd)/sizeof(fd[0]); i++) close(fd[i]);
}
