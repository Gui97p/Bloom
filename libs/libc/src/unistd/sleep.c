#include <stdint.h>
#include <stddef.h>
#include <sys/sleep.h>
#include <sys/types.h>

ssize_t sleep(int ms) {
    return (ssize_t)sys_sleep(ms);
}
