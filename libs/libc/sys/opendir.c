#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_opendir(const char* path) {
    return syscall1(SYSCALL_OPENDIR, (uintptr_t)path);
}
