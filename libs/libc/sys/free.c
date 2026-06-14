#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_free(void *ptr) {
    return syscall1(SYSCALL_FREE, (uintptr_t)ptr);
}
