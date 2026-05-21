#include <sys/sys.h>
#include <string.h>

int puts(const char* s) {
    size_t len = strlen(s);
    sys_write(1, s, len);
    sys_write(1, "\n", 1);
    return 0;
}
