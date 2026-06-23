#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_close(int fd) {
    return syscall1(SYSCALL_CLOSE, (uint64_t)fd);
}
