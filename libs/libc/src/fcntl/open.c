#include <stdint.h>
#include <stddef.h>
#include <sys/open.h>
#include <sys/types.h>

ssize_t open(const void* buf, int flags) {
    return (ssize_t)sys_open(buf, flags);
}
