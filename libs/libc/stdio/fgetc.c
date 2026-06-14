#include <stdio.h>
#include <unistd.h>

int fgetc(FILE* stream) {
    char ch;

    if (read(stream->fd, &ch, 1) != 1)
        return EOF;
    
    return (unsigned char)ch;
}
