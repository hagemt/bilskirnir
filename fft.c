#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define N (1 << 3)
#define MAX_SIZE (1 << 30)
#define NEG_TWO_PI_I (-2 * M_PI * _Complex_I)

typedef double complex fft_t;
typedef fft_t (*gen_t)();

static size_t successors_counter = 0;
static size_t squares_counter = 0;
static size_t powers_counter = 0;

void
fft(fft_t * __restrict__ x, size_t n, size_t s, fft_t * __restrict__ result)
{
	register size_t i;
	size_t m, z;
	fft_t t[2], * __restrict__ l, * __restrict__ r;
	if (n < 2) {
		/* base case, length 1 */
		result[0] = x[0];
	} else {
		/* m is n/2, z is 2s */
		m = (n >> 1);
		z = (s << 1);
		/* produce left and right solutions */
		l = malloc(m * sizeof(fft_t));
		r = malloc(m * sizeof(fft_t));
		fft(x, m, z, l);
		fft(x + s, m, z, r);
		/* add twiddle factors */
		for (i = 0; i < m; ++i) {
			t[0] = l[i];
			t[1] = cexp(NEG_TWO_PI_I * i / n);
			l[i] = t[0] + t[1] * r[i];
			r[i] = t[0] - t[1] * r[i];
		}
		/* combine results */
		for (i = 0; i < m; ++i) {
			result[i] = l[i];
		}
		for (i = 0; i < m; ++i) {
			result[m + i] = r[i];
		}
		/* cleanup */
		free(l);
		free(r);
	}
}

inline void
fft_try(fft_t * __restrict__ a, size_t alen, fft_t * __restrict__ result)
{
	register size_t i;
	/* check all for power of two */
	for (i = 1; i < MAX_SIZE; i <<= 1) {
		if (i == alen) {
			fft(a, alen, 1, result);
			return;
		}
	}
	#ifndef NDEBUG
	fprintf(stderr, "[error] '%lu' (not a power of two)\n", (long unsigned)(alen));
	#endif
}

/* array functions */

inline fft_t
constants()
{
	return N;
}

inline fft_t
successors()
{
	return ++successors_counter;
}

inline fft_t
squares()
{
	++squares_counter;
	return squares_counter * squares_counter;
}

inline fft_t
powers()
{
	++powers_counter;
	return (1 << powers_counter);
}

inline void
fft_fill(fft_t *a, size_t alen, gen_t func)
{
	register size_t i;
	if (func == NULL) {
		func = &successors;
	}
	for (i = 0; i < alen; ++i) {
		a[i] = (*func)();
	}
}

inline void
fft_print(const char *label, fft_t *a, size_t alen) {
	register size_t i;
	printf("%s [\n", label);
	for (i = 0; i < alen; ++i) {
		printf("\t%f + %f\n", creal(a[i]), cimag(a[i]));
	}
	printf("]\n");	
}

inline void
fft_reset()
{
	successors_counter = 0;
	squares_counter = 0;
	powers_counter = 0;
}

#define NUM_GEN 5

int
main(void)
{
	register size_t i;
	fft_t input[N], output[N];
	gen_t generator[NUM_GEN] =
		{ NULL, &constants, &successors, &squares, &powers };
	/* try out each generator */
	for (i = 0; i < NUM_GEN; ++i) {
		fft_fill(input, N, generator[i]);
		fft_print("BEFORE:", input, N);
		fft_try(input, N, output);
		fft_print("AFTER:", output, N);
		fft_reset();
	}
	return (EXIT_SUCCESS);
}
