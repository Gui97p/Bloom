#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

int fputs(const char* str, FILE* stream) {
    size_t len = strlen(str);

    return fwrite(str, 1, len, stream) == len ? 0 : EOF;
}
