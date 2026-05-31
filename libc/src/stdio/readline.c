#include <stdio.h>

char* readline(char* buf, int size) {
    int i = 0;

    while (1) {
        int c = getchar();

        if (c == '\n') {
            putchar('\n');
            break;
        }

        if (c == '\b') {
            if (i > 0) {
                i--;

                putchar('\b');
                putchar(' ');
                putchar('\b');
            }

            continue;
        }

        if (i < size - 1) {
            buf[i++] = c;
            putchar(c);
        }
    }

    buf[i] = '\0';

    return buf;
}