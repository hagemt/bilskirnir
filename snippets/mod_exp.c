#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 64

int
mod_exp(int base, int exp, int mod)
{
	int ans = 1;
	while (exp > 0) {
		if (exp & 1) {
			ans = ans * base % mod;
		}
		exp = exp >> 1;
		base = base * base % mod;
	}
	return ans;
}

int
main(int argc, char ** argv) {
	int b, e, m;
	char * s;
	while (--argc) {
		s = strtok(argv[argc], " ");
		if (s) { b = atoi(s); }
		s = strtok(NULL, " ");
		if (s) { e = atoi(s); }
		s = strtok(NULL, " ");
		if (s) { m = atoi(s); }
		printf("%d^%d = %d (mod %d)\n", b, e, mod_exp(b, e, m), m);
	}
	return argc;
}
