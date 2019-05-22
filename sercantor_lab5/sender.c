#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    for( int i = 0; i < 10; i++ ) {
	printf("I am the sender and my PID is: %d\n", getpid());
	kill(24403, SIGUSR1);
	sleep(2);
    }
    kill(24403,SIGUSR2);
    return 0;
}
