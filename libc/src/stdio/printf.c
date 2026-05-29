#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
                char c = (char)va_arg(args, int);
                putchar(c);
                break;
            }

            case 's': {
                char *s = va_arg(args, char*);
                while (*s)
                    putchar(*s++);
                break;
            }

            case 'i':
            case 'd': {
                int n = va_arg(args, int);

                char buf[32];
                itoa(n, buf, 10);

                char *p = buf;
                while (*p)
                    putchar(*p++);
                break;
            }

            case 'u': {
                unsigned int n = va_arg(args, unsigned int);

                char buf[32];
                utoa(n, buf, 10);

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

            case 'X': {
                unsigned int n = va_arg(args, unsigned int);

                char buf[32];
                utoa(n, buf, 16);

                for (char *p = buf; *p; p++) {
                    if (*p >= 'a' && *p <= 'f')
                        *p -= 32;
                }

                char *p = buf;
                while (*p)
                    putchar(*p++);

                break;
            }

            case 'p': {
                void *ptr = va_arg(args, void*);

                putchar('0');
                putchar('x');

                char buf[32];
                utoa((unsigned long)ptr, buf, 16);

                char *p = buf;
                while (*p)
                    putchar(*p++);

                break;
            }

            case '%':
                putchar('%');
                break;
            
            default:
                putchar('%');
                putchar(*fmt);
                break;
        }

        fmt++;
    }

    va_end(args);
    return 0;
}