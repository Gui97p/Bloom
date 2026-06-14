#include <stdio.h>
#include <string.h>

int puts(const char* s) {
    fputs(s, stdout);
    fputc('\n', stdout);

    return 0;
}
