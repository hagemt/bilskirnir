#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#define N 3
#define TWICE(X) ((X) << 1)

inline const double complex
r(size_t a, size_t b) {
	a += rand() % TWICE(N);
	b += rand() % TWICE(N);
	return (int)(N - a) + (int)(N - b) * I;
}

typedef const double complex (*func_t)(size_t, size_t);

void
fill_square(double complex data[][N], size_t len, func_t func)
{
	register size_t i, j;
	for (i = 0; i < len; ++i) {
		for (j = 0; j < len; ++j) {
			data[i][j] = (*func)(i, j);
		}
	}
}

inline const double
det(double complex data[][N])
{
	register double complex a, b, c;
	a = data[1][1] * data[2][2] - data[1][2] * data[2][1];
	b = data[1][0] * data[2][2] - data[1][2] * data[2][0];
	c = data[1][0] * data[2][1] - data[1][1] * data[2][0];
	return cabs(data[0][0] * a - data[0][1] * b + data[0][2] * c);
}

void
print_square(const char *label, double complex data[][N], size_t len)
{
	register size_t i, j;
	printf("%s (%5.2f):\n", label, det(data));
	for (i = 0; i < len; ++i) {
		printf("\t[");
		for (j = 0; j < len; ++j) {
			printf(" (%5.2f,%5.2fi)", creal(data[i][j]), cimag(data[i][j]));
		}
		printf(" ]\n");
	}
}

int
main(int argc, char *argv[])
{
	int result;
	double complex A[N][N];
	/* srand(0x6c078965); */
	srand((unsigned int)(time(NULL)));

	fill_square(A, N, &r);
	print_square("System", A, N);

	result = 0; /* TODO compute */

	if (result) {
		fprintf(stderr, "[error] '%i' (result of zgeev)\n", result);
	} else {
		printf("[info] pass (data goes here)\n");
	}
	return result;
}
