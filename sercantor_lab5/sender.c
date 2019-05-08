#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("I am the sender and my PID is: %d\n", getpid());
    system("kill -s USR1 $(pidof -s reciever)");   

}
