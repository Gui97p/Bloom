#include <stdint.h>
#include <stddef.h>
#include <sys/read.h>
#include <sys/types.h>

ssize_t read(int fd, void* buf, size_t size) {
    return (ssize_t)sys_read(fd, buf, size);
}
