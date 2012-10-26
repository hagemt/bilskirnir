#include <stdio.h>
#include <stdlib.h>

struct token { char* begin; struct token* next; } first;
struct die { int count, sides; } roll;

int main(int argc, char** argv) {
	int *fill; char *c; struct token *last;
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s XdY ...\n", argv[0]);
	}
	srand(time(NULL));
	while (--argc) {
		first.begin = argv[argc];
		first.next = NULL;
		last = &first;
		for (c = argv[argc]; *c; ++c) {
			if (*c == 'd' || *c == 'D') {
				*c = '\0';
				last = last->next = malloc(sizeof(first));
				last->begin = c + 1;
				last->next = NULL;
			}
		}
/*
		if (!first.next) {
			if ((roll.count = atoi(first.begin)) > 0) {
				printf("Rolling %i stat lines...\n", roll.count);
				fill = malloc(sizeof(int) * 4);
				while (roll.count) {
					printf("TODO");
					printf(", %i left...\n", --roll.count);
				}
				free(fill);
			} else {
				printf("Skipping invalid argument: %s\n", first.begin);
			}
			continue;
		}
*/
		fill = &(roll.count);
		for (last = &first; last; last = last->next) {
			if (!fill || (*fill = atoi(last->begin)) <= 0) {
				if (*(last->begin)) {
					printf("Skipping invalid argument: %s\n", last->begin);
				}
			} else if (fill == &(roll.count)) {
				fill = &(roll.sides);
			} else if (fill == &(roll.sides)) {
				printf("Rolling %id%i:", roll.count, roll.sides);
				while (roll.count--) {
					printf(" %i", rand() % roll.sides + 1);
				}
				printf("\n");
				fill = NULL;
			}
		}
/*
		for (last = &first; last; last = last->next) {
			if (*(last->begin)) {
				printf("%s\n", last->begin);
			}
		}
*/
		for (last = first.next; last;) {
			first.next = last->next;
			free(last);
			last = first.next;
		}
	}
	return(EXIT_SUCCESS);
}
