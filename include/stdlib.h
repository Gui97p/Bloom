#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdint.h>

int abs(int x);
long labs(long x);
long long llabs(long long x);

char *itoa(int value, char *str, int base);
char *utoa(uint64_t value, char *buf, int base);
int atoi(const char *str);
void free(void *ptr);

#endif