#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream) {
    if (!stream || !ptr) return 0;

    size_t total = size * count;
    const char* src = ptr;

    switch (stream->mode) {
        case _IONBF: {
            ssize_t written = write(stream->fd, ptr, total);

            if (written < 0) return 0;
            return written / size;
        }

        case _IOLBF:
        case _IOFBF: {
            for (size_t i = 0; i < total; i++) {
                stream->buffer[stream->bufferPos++] = src[i];

                bool flush = stream->bufferPos >= stream->bufferSize;

                if (stream->mode == _IOLBF && src[i] == '\n') {
                    flush = true;
                }

                if (flush) {
                    if (fflush(stream) != 0)
                        return i / size;
                }
            }

            return count;
        }
    }

    return 0;
}
