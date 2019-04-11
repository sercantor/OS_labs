#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


void copy_lib(const char* arg1, const char* arg2, const char* argv4)
{
    FILE *fpin;
    FILE *fpout;
    long long int size_of_buffer = atoll(argv4);
    char *array = (char*)malloc(size_of_buffer*sizeof(char));
    fpin = fopen(arg1, "r");
    fpout = fopen(arg2, "w");
    fread(array, size_of_buffer, 1, fpin);
    fwrite(array,size_of_buffer,1, fpout);
    fclose(fpin);
    fclose(fpout);
} 
void copy_system(const char* arg1, const char* arg2, const char* arg4)
{
    long long int size_of_buffer = atoll(arg4);
    char *buf = (char*)malloc(size_of_buffer*sizeof(char));
    int fdin;
    int fdout;
    if ((fdin = open(arg1, O_RDONLY)) == -1)
    {
        printf("Failed to open file. Aborting.\n");
        exit(EXIT_FAILURE);
    }

    if ((fdout= open(arg2,O_CREAT | O_WRONLY, 0777)) == -1)
    {
        printf("Failed to open write file. Aborting.\n");
        exit(EXIT_FAILURE);
    }

    read(fdin, buf, size_of_buffer);
    write(fdout, buf, size_of_buffer);
    
    close(fdin);
    close(fdout);
} 
int main(int argc, const char* argv[])
{
    if(strcmp(argv[3], "system") == 0)
	copy_system(argv[1], argv[2], argv[4]);

    else if (strcmp(argv[3], "lib") == 0) 
	copy_lib(argv[1], argv[2], argv[4]);
}
