#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

char *itoa(int value, char *str, int base);
int atoi(const char *str);
void free(void *ptr);

#endif