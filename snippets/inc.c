#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define OUTPUT_FILE "output.txt"
#define BUFFER_SIZE 1024
/* FIXME strtol is not validated */

int
main(void)
{
  int status;
  long i, l, m;
  size_t n;
  char * buffer, * residue;
  FILE * fpin, * fpout;
  status = (EXIT_SUCCESS);
  fpin = fdopen(0, "r");
  if (fpin) {
    buffer = malloc(BUFFER_SIZE * sizeof(char));
    if (getline(&buffer, &n, fpin) > 0) {
      l = strtol(buffer, &residue, 10);
      fpout = fopen(OUTPUT_FILE, "w");
      if (fpout) {
        fprintf(fpout, "%s\n", buffer);
        for (i = 0; i < l; ++i) {
          if (getline(&buffer, &n, fpin) > 0) {
            m = strtol(buffer, &residue, 10);
            fprintf(fpout, "%li\n", ++m);
          } else {
            break;
          }
        }
        fclose(fpout);
      } else {
        status = (EXIT_FAILURE);
      }
    } else {
      status = (EXIT_FAILURE);
    }
    free(buffer);
    fclose(fpin);
  } else {
    status = (EXIT_FAILURE);
  }
  return status;
}
