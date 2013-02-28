#ifndef UTILITIES_H
#define UTILITIES_H

#include <stddef.h>

int __default_driver(void);
void * __random_data(size_t);

/* aliases for the functions above */
#define DEFAULT __default_driver()
#define DATA(x) __random_data(x)

void __println(const char *, const char *, const char *, ...);

#endif /* UTILITIES_H */
