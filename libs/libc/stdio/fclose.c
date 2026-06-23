#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int fclose(FILE* stream) {
    if (!stream)
        return EOF;
    
    fflush(stream);
    
    close(stream->fd);

    if (stream != stdout && stream != stderr) {
        if (stream->buffer)
            free(stream->buffer);
        
        free(stream);
    }
    
    
    return 0;
}
