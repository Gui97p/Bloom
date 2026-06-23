#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "../libs/libc/stdio/formatter.h"

static void serialPut(void *ctx, char c) {
    (void)ctx;
    write(FD_SERIAL, &c, 1);
}

void serialPrintf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vformat(serialPut, NULL, fmt, args);
    va_end(args);
}

__attribute__((noreturn))
void panic(const char *file, int line, const char *expr) {
    serialPrintf("\n");
    serialPrintf("========================================\n");
    serialPrintf("               PANIC\n");
    serialPrintf("========================================\n");
    serialPrintf("Assertion: %s\n", expr);
    serialPrintf("File: %s\n", file);
    serialPrintf("Line: %d\n", line);
    serialPrintf("========================================\n");

    while (1) {
        __asm__ volatile("hlt");
    }
}
