#ifndef UNISTD_H
#define UNISTD_H

#include <stddef.h>
#include <sys/types.h>

ssize_t write(int fd, const void* buf, size_t size);
void exit(int code);

#endif