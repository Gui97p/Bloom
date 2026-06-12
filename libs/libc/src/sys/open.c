#include <stdint.h>
#include <sys/syscall.h>

int64_t sys_open(const void* buf) {
    return syscall1(SYSCALL_OPEN, (uintptr_t)buf);
}
