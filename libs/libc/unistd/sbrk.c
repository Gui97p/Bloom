#include <stdint.h>
#include <sys/sbrk.h>

void *sbrk(intptr_t increment) {
    return (void*)sys_sbrk(increment);
}
