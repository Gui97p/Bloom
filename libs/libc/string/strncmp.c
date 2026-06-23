#include <stddef.h>

int strncmp (const char *s1, const char *s2, size_t size) {
    size_t i = 0;
    while (i < size && s1[i] && s1[i] == s2[i]) i++;

    if (i == size) return 0;

    return (unsigned char)s1[i] - (unsigned char)s2[i];
}