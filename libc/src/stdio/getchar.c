#include <sys/sys.h>

int getchar() {
    char c;
    sys_read(0, &c, 1);
    return c;
}