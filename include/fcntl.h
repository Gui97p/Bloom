#pragma once

#include <sys/types.h>

enum {
    O_RDONLY        = 0,
    O_WRONLY        = 1,
    O_RDWR          = 2,
    O_CREAT         = 4
};

ssize_t open(void* buf, int flags);