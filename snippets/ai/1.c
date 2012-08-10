#include <string.h>
#include <stdio.h>
#define MESSAGE "Esp qtcde nzyqpcpynp zy esp ezatn zq Lcetqtntlw Tyepwwtrpynp hld spwo le Olcexzfes Nzwwprp ty estd jplc"

int main(void) {
	size_t i, n, l, len;
	n = (size_t)('T' - MESSAGE[0]);
	len = strnlen(MESSAGE, sizeof(MESSAGE));
	for (i = 0; i < len; ++i) {
		if (MESSAGE[i] >= 'A' && MESSAGE[i] <= 'Z') {
			l = (size_t)(MESSAGE[i] - 'A');
			printf("%c", (char)((l + n) % 26) + 'A');
		} else if (MESSAGE[i] >= 'a' && MESSAGE[i] <= 'z') {
			l = (size_t)(MESSAGE[i] - 'a');
			printf("%c", (char)((l + n) % 26) + 'a');
		} else {
			printf("%c", ' ');
		}
	}
	printf(".\n%s.\n", MESSAGE);
	return 0;
}
