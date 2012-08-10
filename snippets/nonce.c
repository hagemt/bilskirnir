#include <stdio.h>
#include <stdlib.h>
#include <gcrypt.h>
#define SIZE 118

int
main(void)
{
	size_t i;
	char buffer[SIZE];
	
	for (i = 0; i + 1 < SIZE / 2; ++i) {
		buffer[i] = (char)(i + 'A');
		printf("%X%X ", (buffer[i] & 0xF0) >> 4, (buffer[i] & 0x0F));
	}
	buffer[i] = '\0';
	printf("00\n%s\n", buffer);

	gcry_create_nonce(buffer + i + 1, SIZE - i - 1);
	buffer[SIZE - 1] = '\0';
	printf("%s\n", buffer + i + 1);
	while (++i < SIZE) {
		printf("%X%X ", (buffer[i] & 0xF0) >> 4, (buffer[i] & 0x0F));
	}
	putchar('\n');

	return EXIT_SUCCESS;
}
