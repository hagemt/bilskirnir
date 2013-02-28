#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	while (--argc) {
		int n = atoi(argv[argc]);
		printf("%i:\t%i\n", n, (n + 1) / 2);
	}
	return (EXIT_SUCCESS);
}
