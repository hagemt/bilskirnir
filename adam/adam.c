#include <stdio.h>
#define SYMBOLS 4
#define OPS "+-*/"

inline void
try_all_combinations_with_replacement(const char * args, const int n)
{
	int i, opi[SYMBOLS];
	if (n <= 0) { return; }

	/* opi stores the "operator indices" (a number in base four)
	 * Start by encoding zero, opi = { 0, ..., 0 };
	 * Then, each number maps to a choice (0321) => (/, *, -)
	 */
	for (i = 0; i < n; ++i) { opi[i] = 0; }

	/* The leftmost (highest) digit of opi being set signals a stop */
	while (opi[0] == 0) {
		/* Dump the current statement, as it is constructed */
		for (i = 0; i + 1 < n; ++i) {
			printf("%c %c ", args[i], OPS[opi[i + 1]]);
		}
		/* Note: there are n numbers and n - 1 operators */
		printf("%c\n", args[i]);

		/* Increment the "ones" place; here, i = n - 1 */
		++opi[i];
		/* Then correct any overflows */
		while (0 < i) {
			if (opi[i] == 4) {
				opi[i] = 0;
				++opi[--i];
			} else {
				--i;
			}
		}
	}
}

int
next_number_permutation(char * a, const int n)
{
	char c;
	int k, l;

	/* Find the largest index, k \in [0, n), such that a[k] < a[k + 1] */
	for (k = n - 2; k >= 0 && a[k] >= a[k + 1]; --k);
	/* No such i means the numbers are in descending order, so stop */
	if (k < 0) { return 0; }

	/* Find the largest index, l \in (k, n), such that a[k] < a[l] */
	for (l = n - 1; k + 1 < l && a[k] >= a[l]; --l);

	/* Swap a[k] and a[l], and then a[k + 1] through a[n] */
	c = a[k];
	a[k] = a[l];
	a[l] = c;

	for (k = k + 1, l = n - 1; k < l; ++k, --l) {
		c = a[k];
		a[k] = a[l];
		a[l] = c;
	}
	return 1;
}

int main(void) {
	char set[SYMBOLS] = { '1', '3', '4', '6' };
	do { try_all_combinations_with_replacement(set, SYMBOLS); }
	while (next_number_permutation(set, SYMBOLS));
	return 0;
}
