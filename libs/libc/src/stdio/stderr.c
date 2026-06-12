#include <stdio.h>
#include <sys/syscall.h>

static char stderrBuffer[BUFSIZ];

FILE stderrFile = {
    .fd = FD_STDERR,
    .buffer = stderrBuffer,
    .bufferSize = BUFSIZ,
    .bufferPos = 0,
    .mode = _IONBF
};

FILE* stderr = &stderrFile;