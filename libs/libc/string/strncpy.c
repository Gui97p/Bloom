#include <stddef.h>

char * strncpy(char *restrict to, const char *restrict from, size_t size) {
    size_t i = 0;

    while (i < size && from[i] != '\0') {
        to[i] = from[i];
        i++;
    }

    while (i < size) {
        to[i] = '\0';
        i++;
    }

    return to;
}
