#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_spawn(const void* buf) {
    return syscall1(SYSCALL_SPAWN, (uintptr_t)buf);
}
