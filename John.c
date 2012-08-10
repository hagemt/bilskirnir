/*
 ============================================================================
 Name        : John.c
 Author      : Tor E Hagemann
 Version     : 0.1
 Copyright   : This code is in the public domain.
 Description : A simple Conway's Game of Life emulator.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long word_t;
#define WORD_SIZE (sizeof(word_t) << 3)

int main(void) {
	printf("Size of word: %lu bits\n", WORD_SIZE);
  /* TODO write horton in C */
	return(EXIT_SUCCESS);
}
