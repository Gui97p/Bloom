#include <sys/sys.h>

int getchar() {
    char c;
    sys_read(FD_STDIN, &c, 1);
    return c;
}