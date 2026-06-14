#include <stdio.h>

char* gets(char* buf, int size) {
    int i = 0;

    while (i < size - 1) {
        int c = getchar();

        if (c == '\n')
            break;

        buf[i++] = c;
    }

    buf[i] = '\0';
    return buf;
}