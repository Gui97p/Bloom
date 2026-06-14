#include <stdio.h>
#include <unistd.h>

int fputc(int c, FILE* stream) {
    char ch = c;

    if (write(stream->fd, &ch, 1) != 1)
        return EOF;
    
    return c;
}
