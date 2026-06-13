#include <stdint.h>
#include <stddef.h>
#include <sys/close.h>
#include <sys/types.h>

ssize_t close(int fd) {
    return (ssize_t)sys_close(fd);
}
