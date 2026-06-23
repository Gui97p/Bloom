#include <stdlib.h>
#include <string.h>
#include "formatter.h"

static void emitString(putcf put, void *ctx, const char *str) {
    while (*str)
        put(ctx, *str++);
}

int vformat(putcf put, void *ctx, const char *fmt, va_list args) {
    int written = 0;

    while (*fmt) {
        if (*fmt != '%') {
            put(ctx, *fmt++);
            written++;
            continue;
        }

        fmt++;

        switch (*fmt) {
            case '%':
                put(ctx, '%');
                written++;
                break;

            case 'c': {
                char c = (char)va_arg(args, int);
                put(ctx, c);
                written++;
                break;
            }

            case 's': {
                char* str = va_arg(args, char*);
                
                emitString(put, ctx, str ? str : "(null)");
                written += strlen(str);

                break;
            }

            case 'i':
            case 'd': {
                int n = va_arg(args, int);

                char buf[16];
                itoa(n, buf, 10);

                emitString(put, ctx, buf);
                written += strlen(buf);

                break;
            }

            case 'u': {
                unsigned n = va_arg(args, unsigned);

                char buf[16];
                utoa(n, buf, 10);

                emitString(put, ctx, buf);
                written += strlen(buf);

                break;
            }

            case 'x': {
                unsigned n = va_arg(args, unsigned);

                char buf[16];
                utoa(n, buf, 16);

                emitString(put, ctx, buf);
                written += strlen(buf);

                break;
            }

            case 'X': {
                uint64_t n = va_arg(args, unsigned);

                char buf[32];
                utoa(n, buf, 16);

                emitString(put, ctx, buf);
                written += strlen(buf);

                break;
            }

            case 'p': {
                uintptr_t ptr = va_arg(args, uintptr_t);

                emitString(put, ctx, "0x");

                char buf[32];
                utoa(ptr, buf, 16);

                emitString(put, ctx, buf);
                written += strlen(buf);
                
                break;
            }
        }

        fmt++;
    }

    return written;
}