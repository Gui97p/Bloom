#pragma once

#include <stdarg.h>

typedef void (*putcf)(void *ctx, char c);

int vformat(putcf put, void *ctx, const char *fmt, va_list args);
