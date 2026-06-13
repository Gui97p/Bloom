#include <stdio.h>

char* fgets(char* buf, int size, FILE* stream) {
    if (size <= 0)
        return NULL;

    int i = 0;

    while (i < size - 1) {
        int c = fgetc(stream);

        if (c == EOF)
            break;

        buf[i++] = c;

        if (c == '\n')
            break;
    }

    if (i == 0)
        return NULL;

    buf[i] = '\0';

    return buf;
}
