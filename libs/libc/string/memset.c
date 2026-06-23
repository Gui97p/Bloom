#include <stddef.h>

void *memset(void *ptr, int value, size_t num) {
    void* d = ptr;
    unsigned char v = (unsigned char)value;

    asm volatile (
        "cld\n"
        "rep stosb"
        : "+D"(d), "+c"(num)
        : "a"(v)
        : "memory"
    );

    return ptr;
}
