#include <stdio.h>
#include <unistd.h>

int fflush(FILE* stream) {
    if (!stream)
        return -1;

    if (stream->bufferPos == 0)
        return 0;

    ssize_t written = write(stream->fd, stream->buffer, stream->bufferPos);

    if (written < 0)
        return EOF;

    stream->bufferPos = 0;

    return 0;
}
