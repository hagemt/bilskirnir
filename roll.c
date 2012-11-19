#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main(argc, argv)
	int argc;
	char *argv[];
{
	/* Really limit the stack */
	register char *c;
	int count, sides, *ptr;
	struct token {
		char *data;
		struct token *next;
	} first, *last;
	/* Check arguments */
	if (argc == 1) {
		fprintf(stderr, "USAGE: %s XdY ...\n", *argv);
	}
	srand((unsigned int) (time(NULL)));
	/* Tokenize each argument, forward LIFO */
	while (--argc) {
		first.data = argv[argc];
		first.next = NULL;
		last = &first;
		/* Each argument needs to be masked */
		for (c = argv[argc]; *c; ++c) {
			/* Mark token on numeric characters */
			if (!isdigit(*c)) {
				*c = '\0';
				last->next = malloc(sizeof(struct token));
				last = last->next;
				last->data = c + sizeof(char);
				last->next = NULL;
			}
		}
		ptr = &count;
		/* Deduce amount and sided-ness of die/dice */
		for (last = &first; last; last = last->next) {
			/* In the most eccentric way possible */
			if ((*ptr = atoi(last->data)) <= 0) {
				continue;
			} else if (ptr == &count) {
				ptr = &sides;
			} else if (ptr == &sides) {
				printf("Rolling %id%i:", count, sides);
				while (count--) {
					printf(" %i", (rand() % sides) + 1);
				}
				printf("\n");
				ptr = &count;
			}
		}
		/* The most confusing cleanup ever */
		while ((last = first.next)) {
			first.next = last->next;
			free(last);
		}
	}
	return(EXIT_SUCCESS);
}
