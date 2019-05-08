#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void handler(int num)
{
    /* using write function because we are signal handling */
    switch(num) {
	case SIGTERM:
	    write(STDOUT_FILENO, "SIGTERM Recieved\n,", 20);
	    break;
	case SIGINT:
	    write(STDOUT_FILENO, "SIGINT Recieved\n,", 20);
	    break;
	case SIGUSR1:
	    write(STDOUT_FILENO, "SIGUSR1 Recieved\n", 20);
	    break;
	case SIGTSTP:
	    write(STDOUT_FILENO, "SIGTSPT Recieved\n,", 20);
	    break;
	default:
	    write(STDOUT_FILENO, "Other SIG Recieved\n", 25);
	    break;

    }
}
int main(int argc, char *argv[])
{
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    signal(SIGTSTP, handler);
    signal(SIGUSR1, handler);

    while(1) {
	printf("I'm here and my pid is %d\n", getpid());
	sleep(1);
    }
   
}
