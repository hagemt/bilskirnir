#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define MODE greedy
#define ITERATIONS 1 << 10
#define MAX_SIZE 1 << 20

typedef int type;
typedef unsigned int size_type;

inline void swap(type* x, type* y) {
	if (*x != *y) { *x ^= *y; *y ^= *x; *x ^= *y; }
}

/*
void quicksort(type* a, size_type l, size_type r) {
	if (l < r) {
		size_type left = l, right = r, pivot = l + (r - l) / 2;
		while (left <= pivot && right >= pivot) {
			while (a[left] < a[pivot] && left <= pivot) { ++left; }
			while (a[right] > a[pivot] && right >= pivot) { --right; }
			swap(a + left, a + right);
			if (left == pivot) { pivot = ++right; }
			else if (right == pivot) { pivot = --left; }
			++left; --right;
		}
		if (pivot > l) { quicksort(a, l, pivot - 1); }
		if (pivot < r) { quicksort(a, pivot + 1, r); }
	}
}
*/

size_type greedy(type* a, size_type l, size_type r) {
	size_type i, index = l;
	for (i = l; i < r; ++i) {
		if (a[i] < a[r]) {
			swap(a + i, a + index++);
		}
	}
	swap(a + index, a + r);
	return index;
}

size_type median(type* a, size_type l, size_type r) {
	swap(a + l + (r - l) / 2, a + r);
	return greedy(a, l, r);
}

size_type randomized(type* a, size_type l, size_type r) {
	swap(a + rand() * (r - l) + l, a + r);
	return greedy(a, l, r);
}


void quicksort(type* a, size_type l, size_type r,
		size_type (*pivot_selection_mode)(type*, size_type, size_type)) {
	if (l < r) {
		size_type pivot = (*pivot_selection_mode)(a, l, r);
		if (pivot > l) { quicksort(a, l, pivot - 1, pivot_selection_mode); }
		if (pivot < r) { quicksort(a, pivot + 1, r, pivot_selection_mode); }
	}
}

void test() {
	size_type l, i, j; time_t start, end; srand(time(NULL));
	printf("QUICKSORT RUNNING-TIME ANALYSIS FOR n IN RANGE {%i..%i}\n", ITERATIONS, MAX_SIZE);
	printf("n\ttime (sec) averaged over %i iterations\n", ITERATIONS);
	for (l = ITERATIONS; l <= MAX_SIZE; l <<= 1) {
		double elapsed = 0;
		type* a = malloc(l * sizeof(type));
		for (j = 0; j < l; ++j) { a[j] = j; }
		for (i = 0; i < ITERATIONS; ++i) {
			for (j = 0; j < l; ++j) { swap(a + rand() % l, a + rand() % l); }
			time(&start); quicksort(a, 0, l - 1, MODE); time(&end); elapsed += difftime(end, start);
			for (j = 1; j < l; ++j) { assert(a[j - 1] <= a[j]); }
		}
		elapsed /= ITERATIONS; free(a);
		printf("%i\t%fs\n", l, elapsed);
	}
}
