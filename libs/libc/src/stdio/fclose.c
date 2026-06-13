#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int fclose(FILE* stream) {
    if (!stream)
        return EOF;
    
    close(stream->fd);
    free(stream);

    return 0;
}
