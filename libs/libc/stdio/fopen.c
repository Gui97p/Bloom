#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

FILE* fopen(const char* path, const char* mode) {
    int flags = 0;

    switch (mode[0]) {
        case 'r': {
            flags = O_RDONLY;
            break;
        }

        case 'w': {
            flags = O_WRONLY | O_CREAT;
            break;
        }
        
        case 'a': {
            flags = O_WRONLY | O_CREAT;
            break;
        }

        default: {
            return NULL;
        }
    }

    int fd = open(path, flags);

    if (fd < 0)
        return NULL;

    FILE* f = malloc(sizeof(FILE));

    if (!f) {
        close(fd);
        return NULL;
    }

    f->fd = fd;
    f->buffer = malloc(BUFSIZ);
    f->bufferSize = 0;
    f->bufferPos = 0;
    f->mode = _IOFBF;

    return f;
}
