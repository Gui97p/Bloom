#include <stdint.h>
#include <stddef.h>
#include <sys/seek.h>
#include <sys/types.h>

ssize_t lseek(int fd, size_t size) {
    return (ssize_t)sys_seek(fd, size);
}