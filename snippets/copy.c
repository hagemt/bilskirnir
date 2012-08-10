#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OUTPUT_FILE "output.txt"
#define BUFFER_SIZE 1024

int
main(void)
{
  ssize_t r, w;
  char buffer[BUFFER_SIZE];
  int fd = creat(OUTPUT_FILE, 00644);
  if (fd > 0) {
    while ((r = read(0, buffer, BUFFER_SIZE)) > 0) {
      w = write(fd, buffer, r);
      if (r != w) {
        fprintf(stderr, "Lost %li bytes!\n", (long)(r - w));
      }
    }
    close(fd);
  }
  return (EXIT_SUCCESS);
}
