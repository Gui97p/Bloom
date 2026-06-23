#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_mkdir(void* buf) {
    return syscall1(SYSCALL_MKDIR, (uintptr_t)buf);
}
