#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdint.h>

char *itoa(int value, char *str, int base);
char *utoa(uint64_t value, char *buf, int base);
int atoi(const char *str);
void free(void *ptr);

#endif