#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static int global_counter = 0;

void handler(int signum) {
    if( signum == SIGUSR1 ) {
	global_counter++;
    }
    else if( signum == SIGUSR2 ) {
	printf("the number of recieved signals: %d\n", global_counter);
    }
}

int main() {
	
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    while( 1 ) {
	printf("I am the reciever, my pid is %d\n", getpid());
	sleep(2);
    }
}
