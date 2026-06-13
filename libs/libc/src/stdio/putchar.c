#include <stdio.h>

int putchar(char c) {
    return fputc((char)c, stdout);
}

