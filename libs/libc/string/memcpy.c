#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t num) {
    void* d = dest;
    const void* s = src;

    asm volatile (
        "cld\n"
        "rep movsb"
        : "+D"(d), "+S"(s), "+c"(num)
        :
        : "memory"
    );

    return dest;
}
