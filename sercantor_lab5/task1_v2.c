#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


void handler(int signum)
{
    printf("Recieved signal %d\n", signum);
    sleep(5);
}

int main()
{
    printf("%d\n", getpid());
    
    sigset_t newsig;

    struct sigaction action_setup = { {handler}, newsig, 0 };
    sigaction(SIGTERM, &action_setup, 0);
    sigaction(SIGINT, &action_setup, 0);
    sigaction(SIGTSTP, &action_setup, 0);
    sigaction(SIGUSR1, &action_setup, 0);

    while(1) sleep(5);
}
