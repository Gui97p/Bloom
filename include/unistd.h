#pragma once

#include <stddef.h>
#include <sys/types.h>

ssize_t write(int fd, const void* buf, size_t size);
ssize_t read(int fd, void* buf, size_t size);
ssize_t close(int fd);
ssize_t lseek(int fd, size_t size);
ssize_t sleep(int ms);
ssize_t spawn(void* buf);
void *sbrk(intptr_t increment);
