#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>

size_t fread(void* ptr, size_t size, size_t count, FILE* stream) {
    ssize_t bytes = read(stream->fd, ptr, size * count);

    if (bytes < 0)
        return 0;
    
    return bytes / size;
}
