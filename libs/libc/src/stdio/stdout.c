#include <stdio.h>
#include <sys/sys.h>

static char stdoutBuffer[BUFSIZ];

FILE stdoutFile = {
    .fd = FD_SERIAL,
    .buffer = stdoutBuffer,
    .bufferSize = BUFSIZ,
    .bufferPos = 0,
    .mode = _IOLBF
};

FILE* stdout = &stdoutFile;