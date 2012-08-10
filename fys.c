#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define N 5

int
main(void)
{
  int i, r, a[N];
  srand((unsigned int)(time(NULL)));
  for (i = 0; i < N; ++i) {
    a[i] = i;
  }
  for (i = 0; i < N; ++i) {
    r = rand() % (N - i) + i;
    if (r != i) {
      a[i] ^= a[r];
      a[r] ^= a[i];
      a[i] ^= a[r];
    }
  }
  for (i = 0; i < N; ++i) {
    printf("%i ", a[i]);
  }
  putchar('\n');
  return EXIT_SUCCESS;
}
