#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>

int sys_readdir(int index, void* buf) {
    return syscall2(SYSCALL_READDIR, (uint64_t)index, (uintptr_t)buf);
}
