#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <sys/types.h>

ssize_t strlen(const char* s);
int strcmp (const char *s1, const char *s2);
int strncmp (const char *s1, const char *s2, size_t size);
char *strcpy(char *restrict to, const char *restrict from);
char *strncpy(char *restrict to, const char *restrict from, size_t size);
void *memset(void *ptr, int value, size_t num);
void *memcpy(void *dest, const void *src, size_t num);
void *memmove(void *dest, const void *src, size_t num);

#endif