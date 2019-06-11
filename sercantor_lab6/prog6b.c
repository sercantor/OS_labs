#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>

#define BUF_SIZE 256
  
int main(int argc, char *argv[]) {
    
    int fd; 
    char *fifo = "myfifo"; 
    mkfifo(fifo, 0666); 
  
    char read_arr[BUF_SIZE]; 
    fd = open(fifo, O_WRONLY); 

    char write_arr[BUF_SIZE];
    fgets(write_arr, BUF_SIZE, stdin);

    write(fd, write_arr, strlen(write_arr)+1); 
    close(fd); 

    fd = open(fifo, O_RDONLY); 
    read(fd, read_arr, sizeof(read_arr)); 
    close(fd); 

    return 0; 
} 

