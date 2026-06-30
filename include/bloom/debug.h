#pragma once

#include <stdio.h>

#define ASSERT(expr) \
do { \
    if (!(expr)) \
        panic(__FILE__, __LINE__, #expr); \
} while (0)

#ifdef DEBUG
#define DPRINTF(...) serialPrintf(__VA_ARGS__)
#else
#define DPRINTF(...)
#endif

void panic(const char *file, int line, const char *expr);
void serialPrintf(const char *fmt, ...);