#include <stddef.h>

char* strtok(char* str, const char* delim) {
    static char* next;

    if (str)
        next = str;

    if (!next)
        return NULL;

    while (*next) {
        int found = 0;

        for (const char* d = delim; *d; d++) {
            if (*next == *d) {
                found = 1;
                break;
            }
        }

        if (!found)
            break;

        next++;
    }

    if (*next == '\0') {
        next = NULL;
        return NULL;
    }

    char* token = next;

    while (*next) {
        for (const char* d = delim; *d; d++) {
            if (*next == *d) {
                *next = '\0';
                next++;
                return token;
            }
        }

        next++;
    }

    next = NULL;
    return token;
}