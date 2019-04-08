#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


void copy_lib(const char* arg1, const char* arg2)
{
    FILE *fpin;
    FILE *fpout;
    fpin = fopen(arg1, "r");
    fpout = fopen(arg2, "w");
    int c;
    while((c = fgetc(fpin)) != EOF)
       fputc(c, fpout);
    fclose(fpin);
    fclose(fpout);
} 
void copy_system(const char* arg1, const char* arg2, const char* arg4)
{
    int size_of_buffer = atoi(arg4);
    int buf[size_of_buffer];
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
    while((read(fdin, buf, size_of_buffer)) != 0) {
	write(fdout, buf, size_of_buffer);
    }
    close(fdin);
    close(fdout);
} 
int main(int argc, const char* argv[])
{
    if(strcmp(argv[3], "system") == 0){
    clock_t t; 
    t = clock(); 
    copy_system(argv[1], argv[2], argv[4]);
    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  
    printf("System call copy took %f seconds\n", time_taken); 
   }


    else if (strcmp(argv[3], "lib") == 0) {
    clock_t t1; 
    t1 = clock(); 
    copy_lib(argv[1], argv[2]);
    t1 = clock() - t1; 
    double time_taken1 = ((double)t1)/CLOCKS_PER_SEC; // in seconds 
  
    printf("Lib call copy took %f seconds\n", time_taken1); 
    }
}
