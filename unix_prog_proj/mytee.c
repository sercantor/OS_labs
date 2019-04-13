#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void write_to_file(int fd[], int argc)
{

    char *buf = malloc(BUFFER_SIZE*sizeof(char));
    int bytes_read;
    while((bytes_read = read(STDIN_FILENO, buf, sizeof(buf)-1)) > 0) {
	/*set the last byte to null, this will ensure we won't get random characters*/
	buf[bytes_read] = 0x00;
	/*write to stdout*/
	printf("%s", buf);
	/*write to file*/
	for(int i = 0; i < argc; i++) write(fd[i], buf, bytes_read);
    }

    free(buf);
} 

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
		 for(int i = 2; i < argc; i++) {
		 fd[i] = open(argv[i], O_WRONLY | O_APPEND | O_CREAT, S_IWUSR | S_IRUSR); 
		    if(fd[i] == -1) {
			perror("cannot open file, exiting");
			exit(1);
		     } 
		 }
		write_to_file(&fd[2],argc);
		break;
	    case 't':
		 for(int i = 2; i < argc; i++) {
		 fd[i] = open(argv[i], O_WRONLY | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR); 
		    if(fd[i] == -1) {
			perror("cannot open file, exiting");
			exit(1);
		    } 
		 }
		write_to_file(&fd[2],argc);
		break;
	    default:
		printf("invalid option\n");
		exit(1);
	    }
    }
    /*if they don't want to use options, just create file(s), error if exists (EXCL)*/
    else {
	for(int i = 1; i < argc; i++) {
	    fd[i] = open(argv[i], O_WRONLY | O_CREAT | O_EXCL, S_IWUSR | S_IRUSR); 
	    if(fd[i] == -1) {
		perror("cannot open file, exiting");
		exit(1);
	    }
	} 
	write_to_file(&fd[1],argc);
    }


    /*after operation is done, close all files*/
    for(int i = 1; i < argc; i++) close(fd[i]);

    return 0;

}

