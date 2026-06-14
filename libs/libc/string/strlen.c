#include <sys/types.h>

ssize_t strlen(const char* s) {
    ssize_t i = 0;
    while (s[i]) i++;
    return i;
}