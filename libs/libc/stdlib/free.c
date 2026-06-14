#include <sys/free.h>
#include <sys/types.h>

ssize_t free(void *ptr) {
    return sys_free(ptr);
}