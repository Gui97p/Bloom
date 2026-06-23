#include <stdio.h>
#include <sys/syscall.h>

static char stdoutBuffer[BUFSIZ];

FILE stdoutFile = {
    .fd = FD_STDOUT,
    .buffer = stdoutBuffer,
    .bufferSize = BUFSIZ,
    .bufferPos = 0,
    .mode = _IOLBF
};

FILE* stdout = &stdoutFile;
