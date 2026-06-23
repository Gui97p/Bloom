#include <stdint.h>
#include <sys/syscall.h>

int64_t sys_open(const void* buf, int flags) {
    return syscall2(SYSCALL_OPEN, (uintptr_t)buf, flags);
}
