#include <stdio.h>
#include <unistd.h>

int fflush(FILE* stream) {
    if (!stream)
        return -1;

    if (stream->bufferPos == 0)
        return 0;

    write(
        stream->fd,
        stream->buffer,
        stream->bufferPos
    );

    stream->bufferPos = 0;

    return 0;
}
