/*
 * huffman.c
 *
 *  Created on: Dec 31, 2010
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1UL << (sizeof(char) << 3)

void count(char* filename) {
	unsigned int i; char* count = malloc(BUFFER_SIZE * sizeof(char));
	char* path = malloc((strlen(filename) + 5) * sizeof(char));
	FILE* ifp = fopen(filename, "rb");
	FILE* ofp = fopen(strcat(strcpy(path, filename), ".tor"), "wb");
	if (ifp && ofp) {
		for (i = 0; i < BUFFER_SIZE; ++i) { count[i] = 0; }
		while ((i = fgetc(ifp)) != EOF) {
			if (i < BUFFER_SIZE) { count[i]++; }
			else { fprintf(stderr, "Invalid data: 0x%X\n", i); }
		}
		for (i = 0; i < BUFFER_SIZE; ++i) {
			fprintf(ofp, "0x%X:\t%u\n", i, count[i]);
		}
		fclose(ifp); fclose(ofp);
	} else {
		fprintf(stderr, "Cannot compress: %s", filename);
	}
	free(path); free(count);
}

typedef struct {
	char data;
	unsigned long int count;
} pair;

int main(int argc, char** argv) {
	unsigned int i;
	pair* BUFFER = malloc(256 * sizeof(pair));
	for (i = 0; i < BUFFER_SIZE; ++i) {
		BUFFER[i].data = i; BUFFER[i].count = 0UL;
	}
	printf("Before:\n");
	for (i = 0; i < BUFFER_SIZE; ++i) {
		printf("[0x%X]:\t%lu\n", BUFFER[i].data, BUFFER[i].count);
	}
	// quicksort(PAIRS, 0, BUFFER_SIZE);
	printf("After:\n");
	for (i = 0; i < BUFFER_SIZE; ++i) {
		printf("[0x%X]:\t%lu\n", BUFFER[i].data, BUFFER[i].count);
	}
	free(BUFFER);
	test();
	return(EXIT_SUCCESS);
}
