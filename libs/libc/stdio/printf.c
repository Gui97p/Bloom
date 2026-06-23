#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "formatter.h"

static void stdoutPut(void *ctx, char c) {
    fputc(c, stdout);
}

int vprintf(const char *fmt, va_list args) {
    return vformat(stdoutPut, stdout, fmt, args);
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = vprintf(fmt, args);

    va_end(args);
    
    return ret;
}
