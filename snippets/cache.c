/*
 * cache.c
 *
 *  Created on: Dec 27, 2010
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */
#include <stdio.h>
#include <stdlib.h>
#define CACHE_SIZE 1 << 10
#define CACHE_SETS 1 << 2

__inline void
get(const size_t** cache, size_t* address)
{
	printf("Cache at %p was asked for address %p", cache, address);
}

__inline void
set(const size_t** cache, size_t* address, size_t value)
{
	printf("Cache at %p was asked for address *%p = %lu", cache, address, value);
}

int main(int argc, char ** argv)
{
//	int i; size_t ** CACHE = malloc(sizeof(size_t*) * CACHE_SETS);
//	for (i = 0; i < CACHE_SETS; ++i) { CACHE[i] = malloc(sizeof(size_t) * (CACHE_SIZE >> CACHE_BITS)); }
	printf("Size of cache: (%i bytes/set x %i sets) = %i bytes\n", CACHE_SIZE / CACHE_SETS, CACHE_SETS, CACHE_SIZE);
//	for (i = 0; i < CACHE_SETS; ++i) { free(CACHE[i]); } free(CACHE);
	return(EXIT_SUCCESS);
}
