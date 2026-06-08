#ifndef SYS_H
#define SYS_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

enum {
    FD_STDIN       = 0,
    FD_STDOUT      = 1,
    FD_STDERR      = 2,
    FD_EVENT       = 3
};

enum {
    SYSCALL_READ   = 0,
    SYSCALL_WRITE  = 1,
    SYSCALL_OPEN   = 2,
    SYSCALL_CLOSE  = 3,
    SYSCALL_INB    = 4,
    SYSCALL_OUTB   = 5,
};

ssize_t sys_write(int fd, const void* buf, size_t count);
ssize_t sys_read(int fd, void* buf, size_t size);
void sys_exit(int status);

#endif