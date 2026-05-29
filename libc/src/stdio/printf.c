#include <stdio.h>

int printf(const char *fmt, ...) {
    while (*fmt) {
        putchar(*fmt);
        fmt++;
    }
    return 0;
}