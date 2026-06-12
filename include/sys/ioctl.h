#pragma once

#include <sys/types.h>

ssize_t ioctl(int fd, int action, void* arg);