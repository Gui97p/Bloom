#include <stdint.h>
#include <sys/syscall.h>

void *sys_sbrk(intptr_t increment) {
    return (void*)syscall1(SYSCALL_SBRK, (intptr_t)increment);
}
