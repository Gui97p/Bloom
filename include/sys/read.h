#pragma once

#include <stddef.h>
#include <sys/types.h>

ssize_t sys_read(int fd, void* buf, size_t size);