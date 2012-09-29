#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef size_t type_t;

type_t
maxof(size_t, ...);

int
main(void)
{
	type_t i, j[1];
	i = j[0] = 0;
	printf("%d\n", (int)(maxof(3, 0, i + 1, j[0] + 2)));
	exit(EXIT_SUCCESS);
}

type_t
maxof(size_t argc, ...)
{
	register size_t i;
	type_t max, arg;
	va_list args;

	/* Start the VA_LIST */
	va_start(args, argc);

	max = va_arg(args, type_t);
	for (i = 1; i < argc; ++i) {
		arg = va_arg(args, type_t);
		if (max < arg) max = arg;
	}

	/* End the VA_LIST */
	va_end(args);

	return max;
}
