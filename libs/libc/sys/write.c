#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_write(int fd, const void* buf, size_t size) {
    return syscall3(SYSCALL_WRITE, (uint64_t)fd, (uintptr_t)buf, (uint64_t)size);
}
