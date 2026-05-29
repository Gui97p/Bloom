#include <sys/sys.h>
#include <string.h>

int puts(const char* s) {
    size_t len = strlen(s);
    sys_write(FD_STDOUT, s, len);
    sys_write(FD_STDOUT, "\n", 1);
    return 0;
}
