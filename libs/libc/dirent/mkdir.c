#include <sys/mkdir.h>

int mkdir(const char* path) {
    return sys_mkdir(path);
}
