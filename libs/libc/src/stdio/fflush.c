#include <stdio.h>
#include <sys/write.h>

int fflush(FILE* stream) {
    if (!stream)
        return -1;

    if (stream->bufferPos == 0)
        return 0;

    sys_write(
        stream->fd,
        stream->buffer,
        stream->bufferPos
    );

    stream->bufferPos = 0;

    return 0;
}