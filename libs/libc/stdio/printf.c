#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "formatter.h"

static void stdoutPut(void *ctx, char c) {
    (void)ctx;

    write(stdout->fd, &c, 1);
}

int vprintf(const char *fmt, va_list args) {
    return vformat(stdoutPut, NULL, fmt, args);
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = vprintf(fmt, args);

    va_end(args);
    
    return ret;
}
