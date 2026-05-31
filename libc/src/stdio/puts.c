#include <stdio.h>
#include <string.h>
#include "file.h"

int puts(const char* s) {
    while (*s) {
        filePutc(stdout, *s++);
    }

    filePutc(stdout, '\n');

    return 0;
}
