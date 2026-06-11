#include <syscalls.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/sys.h>

ssize_t sys_write(int fd, const void* buf, size_t size) {
    return syscall(SYSCALL_WRITE, (uint64_t)fd, (uintptr_t)buf, (uint64_t)size, 0, 0, 0);
}

ssize_t sys_read(int fd, void* buf, size_t size) {
    return syscall(SYSCALL_READ, (uint64_t)fd, (uintptr_t)buf, (uint64_t)size, 0, 0, 0);
}

int64_t sys_open(const void* buf) {
    return syscall(SYSCALL_OPEN, (uintptr_t)buf, 0, 0, 0, 0, 0);
}

int64_t sys_ioctl(int fd, int action, void* arg) {
    return syscall(SYSCALL_IOCTL, fd, action, (uintptr_t)arg, 0, 0, 0);
}

uint64_t sys_malloc(size_t size) {
    return syscall(SYSCALL_MALLOC, size, 0, 0, 0, 0, 0);
}

void sys_exit(int code) {
    // syscall(SYSCALL_CLOSE, (uint64_t)code, 0, 0, 0, 0, 0);
    while (1) {}
}
