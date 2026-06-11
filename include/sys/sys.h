#ifndef SYS_H
#define SYS_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

enum {
    FD_STDIN       = 0,
    FD_STDOUT      = 1,
    FD_STDERR      = 2,
    FD_SERIAL      = 3
};

enum {
    SYSCALL_READ   = 0,
    SYSCALL_WRITE  = 1,
    SYSCALL_OPEN   = 2,
    SYSCALL_CLOSE  = 3,
    SYSCALL_IOCTL  = 4,
    SYSCALL_MALLOC = 5,
    SYSCALL_SPAWN  = 6,
    SYSCALL_REBOOT = 7
};

ssize_t sys_write(int fd, const void* buf, size_t count);
ssize_t sys_read(int fd, void* buf, size_t size);
int64_t sys_open(const void* buf);
int64_t sys_ioctl(int fd, int action, void* arg);
uint64_t sys_malloc(size_t size);
void sys_exit(int status);

#endif