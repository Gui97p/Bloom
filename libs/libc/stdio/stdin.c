#include <stdio.h>
#include <sys/syscall.h>

static char stdinBuffer[BUFSIZ];

FILE stdinFile = {
    .fd = FD_STDIN,
    .buffer = stdinBuffer,
    .bufferSize = BUFSIZ,
    .bufferPos = 0,
    .mode = _IOLBF
};

FILE* stdin = &stdinFile;
