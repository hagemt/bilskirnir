#include <stdio.h>
#include <assert.h>
#define HEIGHT 8
#define WIDTH 19

int main(void) {
  size_t i, j, c[WIDTH];
  char p, input[HEIGHT][WIDTH][2];
  for (i = 0; i < HEIGHT; ++i) {
    for (j = 0; j < WIDTH; ++j) {
      assert((p = getchar()) == '|');
      input[i][j][0] = getchar();
      input[i][j][1] = getchar();
    }
    assert((p = getchar()) == '|');
    assert((p = getchar()) == '\n');
  }
  for (i = 0; i < WIDTH; ++i) {
    scanf("%lu", &c[i]);
  }
  for (i = 0; i < HEIGHT; ++i) {
    for (j = 0; j < WIDTH; ++j) {
      printf("%c%c",
       input[i][c[j] - 1][0],
       input[i][c[j] - 1][1]);
    }
    putchar('\n');
  }
  for (i = 0; i < HEIGHT; ++i) {
    for (j = 0; j < WIDTH; ++j) {
      printf("|%c%c",
       input[i][c[j] - 1][0],
       input[i][c[j] - 1][1]);
    }
    printf("|\n");
  }
  for (i = 0; i < WIDTH; ++i) {
    printf("|%2lu", c[i]);
  }
  printf("|\n");
  return 0;
}
