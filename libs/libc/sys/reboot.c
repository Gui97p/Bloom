#include <sys/syscall.h>

void sys_reboot() {
    syscall0(SYSCALL_REBOOT);
}
