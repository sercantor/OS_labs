#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
#define BUF_SIZE 256

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;
    char buf[BUF_SIZE];
    int fd_pipe;

    if( argc != 2 ) {
	printf("usage: ./a.out [string]\n");
	exit(2);
    }

    if( pipe(fd) == -1 ) {
	perror("pipe");
    }

    pid = fork();
    if( pid == -1 ) { /* error */
	perror("fork");
    }
    else if( pid == 0 ){ /* in child ( write ) */

	if( close(fd[READ_END]) == -1 ) { /* close read end because we're not going to use it */
	    perror("close");
	}
	if( write(fd[WRITE_END], argv[1], strlen(argv[1])) != strlen(argv[1]) )	{ /* write argv[1] */
	    exit(1);
	}
	close(fd[WRITE_END]);
	wait(NULL);
    } else { /* in parent ( listen ) */
	if( close(fd[WRITE_END]) == -1 ) {
	    perror("close");
	}
	while( 1 ) {
	fd_pipe = read(fd[READ_END], buf, BUF_SIZE);
	if( fd_pipe == -1 ) {
	    perror("read");
	}
	if( fd_pipe == 0 ) {
	    break;
	}
	if (write(STDOUT_FILENO, buf, fd_pipe) != fd_pipe)
	    exit(1);
	}
	write(STDOUT_FILENO, "\n", 1);
	close(fd[READ_END]);
    }

}
