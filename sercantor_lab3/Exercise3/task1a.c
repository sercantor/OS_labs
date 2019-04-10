#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

void rand_to_file(int fd, const char* argument)
{
    int size_of_file = atoi(argument);
    char *array = (char*)malloc(size_of_file);

    /*feed the seed with time header and fill the array with rand chars*/
    srand(time(NULL));
    for(int i = 0; i < size_of_file; i++) array[i] = 65 + rand() / (RAND_MAX / (90 - 65 + 1) + 1);
    /*write to fd, with sizeoffile being an argument, array being the buffer*/
    write(fd, array, size_of_file);
}     
int main(int argc, const char* argv[])
{

    if(argc != 3) {
	perror("you have enter two arguments");
	exit(1);
    }
    int fd;
    int result;

    fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, (mode_t)0600);
    if (fd == -1) {
	perror("Error opening file for writing");
        return 1;
    }
    

    clock_t t;
    t = clock();
    rand_to_file(fd, argv[2]);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    
    FILE *fprep = fopen("ex3task1rep.txt","w");
    fprintf(fprep, "time taken by creating file with system call: %f\n", time_taken);

    close(fd);
    return 0;
}
