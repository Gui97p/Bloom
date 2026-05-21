#include <syscalls.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/sys.h>

ssize_t sys_write(int fd, const void* buf, size_t size) {
    return syscall(1, (uint64_t)fd, (uintptr_t)buf, (uint64_t)size, 0, 0, 0);
}

void sys_exit(int code) {
    syscall(60, (uint64_t)code, 0, 0, 0, 0, 0);
    while (1) {}
}
