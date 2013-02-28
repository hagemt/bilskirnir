#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_DIGIT '1'
#define MAX_DIGIT '9'

int next_wo(char *number, size_t len) {
	size_t i, k;
	number[len] = (char) (MAX_DIGIT + 1);
	/* Find least-sig digit that differs by delta from predecessor */
	for (k = len; k > 0; --k) {
		if (number[k - 1] + 1 < number[k]) break;
	}
	/* Stopping condition: no more if there is no such k > 0 */
	if (k == 0) {
		number[len] = '\0';
		return 0;
	}
	/* Update the digits accordingly (monotonic) */
	++number[k - 1];
	if (number[k] > (char) (MAX_DIGIT + k - len)) {
		for (i = k; i < len; ++i) {
			number[i] = (char) (number[i - 1] + 1);
		}
	}
	/* Repair the string */
	number[len] = '\0';
	return 1;
}

void print_all_wo(size_t digits) {
	size_t i, n = 0;
	char *number = (char *) malloc((digits + 1) * sizeof(char));
	/* Set up a numeric string */
	number[digits] = '\0';
	for (i = 0; i < digits; ++i) {
		number[i] = (char) (MIN_DIGIT + i);
		if (number[i] > MAX_DIGIT) {
			fprintf(stderr, "[error] |[%c, %c]| < %lu (too few values)\n",
					MIN_DIGIT, MAX_DIGIT, (long unsigned) digits);
			free(number);
			return;
		}
	}
	/* Increment through all possible values */
	do { printf("%s\n", number); ++n; }
	while (next_wo(number, digits));
	printf("[info] %lu (well-ordered %lu-digit numbers)\n",
			(long unsigned) n, (long unsigned) digits);
	free(number);
}

int main(void) {
	/*
	size_t i, n = (MAX_DIGIT - MIN_DIGIT) + 3;
	for (i = 0; i < n; ++i) {
		printf("Well-ordered numbers of length %lu:\n", (long unsigned) i);
		print_all_wo(i);
	}
	*/
	print_all_wo(0);
	print_all_wo(1);
	print_all_wo(2);
	print_all_wo(3);
	return (EXIT_SUCCESS);
}
