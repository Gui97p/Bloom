#include <stdio.h>
#include <unistd.h>
#include "formatter.h"

static void filePut(void *ctx, char c) {
    fputc(c, ctx);
}

int vfprintf(FILE *stream, const char *fmt, va_list args) {
    return vformat(filePut, stream, fmt, args);
}

int fprintf(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = vfprintf(stream, fmt, args);

    va_end(args);
    
    return ret;
}
