#ifndef SYS_H
#define SYS_H

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>

ssize_t sys_write(int fd, const void* buf, size_t count);

void sys_exit(int status);

#endif