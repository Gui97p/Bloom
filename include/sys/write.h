#pragma once

#include <stddef.h>
#include <sys/types.h>

ssize_t sys_write(int fd, const void* buf, size_t count);
