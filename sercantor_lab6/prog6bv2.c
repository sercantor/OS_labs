#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char const * const FIFO_PATH = "sercan_fifo";
#define BUF_SIZE 6

int main() {
  if( mkfifo(FIFO_PATH, 0777) < 0 ) {
      printf("error mkfifo\n");
      exit(1);
  }
  pid_t child_pid = fork();
  if (child_pid == 0) { /* in child */
    int pipe_read_fd = open(FIFO_PATH, O_RDONLY);
    if( pipe_read_fd < 0 ) {
	printf("error opening\n");
	exit(1);
    }
    char buf[BUF_SIZE];
    while( 1 ) {
      ssize_t num_read = read(pipe_read_fd, buf, sizeof(buf));
      if (num_read == 0) {
        close(pipe_read_fd);
        break;
      } else {
        write(1, buf, num_read);
        write(1, "\n", 2);
      }
    }
  } else {
    // Parent
    int pipe_write_fd = open(FIFO_PATH, O_WRONLY);
    write(pipe_write_fd, "sercantor", 10);
    close(pipe_write_fd);
  }

  return 0;
}

