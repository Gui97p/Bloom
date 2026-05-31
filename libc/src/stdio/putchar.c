#include <stdio.h>
#include "file.h"

int putchar(char c) {
    return filePutc(stdout, (char)c);
}

