#include <stdint.h>
#include <stddef.h>
#include <sys/write.h>
#include <sys/types.h>

ssize_t write(int fd, const void* buf, size_t size) {
    return (ssize_t)sys_write(fd, buf, size);
}