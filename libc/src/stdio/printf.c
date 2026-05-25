#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            putchar(*fmt);
            fmt++;
            continue;
        }

        fmt++;

        switch (*fmt) {
            case 'c': {
                char c = va_arg(args, int);
                putchar(c);
                break;
            }

            case 's': {
                char *s = va_arg(args, char*);
                while (*s)
                    putchar(*s++);
                break;
            }

            case 'd': {
                int n = va_arg(args, int);

                char buf[32];
                itoa(n, buf, 10);

                char *p = buf;
                while (*p)
                    putchar(*p++);
                break;
            }

            case 'x': {
                int n = va_arg(args, int);

                char buf[32];
                itoa(n, buf, 16);

                char *p = buf;
                while (*p)
                    putchar(*p++);
                break;
            }

            case '%':
                putchar('%');
                break;
        }

        fmt++;
    }

    va_end(args);

    return 0;
}