#include <sys/sys.h>

void exit(int code) {
    sys_exit(code);
}
