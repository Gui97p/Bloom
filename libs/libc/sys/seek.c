#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_seek(int fd, size_t size) {
    return syscall2(SYSCALL_SEEK, (uint64_t)fd, (uint64_t)size);
}
