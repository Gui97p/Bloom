#include <stddef.h>
#include <stdint.h>
#include <sys/syscall.h>

uint64_t sys_malloc(size_t size) {
    return syscall1(SYSCALL_MALLOC, size);
}
