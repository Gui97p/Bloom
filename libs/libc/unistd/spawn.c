#include <stdint.h>
#include <stddef.h>
#include <sys/spawn.h>
#include <sys/types.h>

ssize_t spawn(void* buf) {
    return (ssize_t)sys_spawn(buf);
}