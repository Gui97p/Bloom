#include <sys/sys.h>

int putchar(char c) {
    return sys_write(FD_STDOUT, &c, 1);
}

