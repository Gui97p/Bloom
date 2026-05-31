#include <stdio.h>

int filePutc(FILE* stream, char c) {
    stream->buffer[stream->bufferPos++] = c;

    if (stream->bufferPos >= stream->bufferSize) {
        fflush(stream);
    }

    if (stream->mode == _IOLBF && c == '\n') {
        fflush(stream);
    }

    if (stream->mode == _IONBF) {
        fflush(stream);
    }

    return (unsigned char)c;
}
