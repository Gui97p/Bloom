#include <stdint.h>
#include <sys/syscall.h>

int64_t ioctl(int fd, int action, void* arg) {
    return syscall3(SYSCALL_IOCTL, fd, action, (uintptr_t)arg);
}
