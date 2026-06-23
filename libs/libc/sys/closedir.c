#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_closedir(int fd) {
    return syscall1(SYSCALL_CLOSEDIR, fd);
}
