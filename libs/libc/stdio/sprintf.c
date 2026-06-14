#include <stdio.h>
#include <stdarg.h>
#include "formatter.h"

typedef struct {
    char *buf;
    int pos;
} StringCtx;

typedef struct {
    char *buf;
    size_t size;
    size_t pos;
} SnprintfCtx;

static void stringPut(void *ctx, char c) {
    StringCtx *s = ctx;

    s->buf[s->pos++] = c;
}

int vsprintf(char *str, const char *fmt, va_list args) {
    StringCtx ctx = {
        .buf = str,
        .pos = 0
    };

    int ret = vformat(stringPut, &ctx, fmt, args);

    str[ctx.pos] = '\0';
    return ret;
}

int sprintf(char *str, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = vsprintf(str, fmt, args);

    va_end(args);
    
    return ret;
}

static void snprintfPut(void *ctx, char c) {
    SnprintfCtx *s = ctx;

    if (s->pos + 1 < s->size) {
        s->buf[s->pos] = c;
    }

    s->pos++;
}

int vsnprintf(char *str, size_t size, const char *fmt, va_list args) {
    SnprintfCtx ctx = {
        .buf = str,
        .size = size,
        .pos = 0
    };

    int ret = vformat(snprintfPut, &ctx, fmt, args);

    if (size > 0) {
        size_t end = ctx.pos < size - 1 ? ctx.pos : size - 1;

        str[end] = '\0';
    }

    return ret;
}

int snprintf(char *str, size_t size, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = vsnprintf(str, size, fmt, args);

    va_end(args);

    return ret;
}
