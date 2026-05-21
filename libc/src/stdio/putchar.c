#include <sys/sys.h>

int putchar(char c) {
    return sys_write(1, &c, 1);
}

