#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>


int main(int argc, char* argv[])
{
    pid_t pid;

    if(argc != 4) {
        perror("wrong number of arguments");
    }
 
    char *temp = argv[0];
    char *temp1 = argv[1];
    char *temp2 = argv[2];
    char *temp3 = argv[3];

    char *const arg_list[] = {argv[0], argv[1], argv[2],argv[3], NULL};
    // Write a child process which execute a process ./calc with  argv[1], argv[2] oraz argv[3] parameteres
    //where argv[1] - first number, argv[2] - operation  (+-x/),  argv[3]  - second number  
    //use table methods to pass argument to the program (argv) 
    if((pid = fork()) == -1) {
	perror("fork error");
	exit(1);
    }
    else if(pid == 0) {
	   //execv("/bin/calc", arg_list);
       //execl("/bin/calc", temp, temp1, temp2, temp3, NULL);
       execvp("/bin/calc", arg_list);
 return 0;
    }
}