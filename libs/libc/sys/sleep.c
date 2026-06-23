#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

ssize_t sys_sleep(int ms) {
    return syscall1(SYSCALL_SLEEP, (uint64_t)ms);
}
