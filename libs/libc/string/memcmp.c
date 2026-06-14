#include <stddef.h>

int memcmp(const void* a, const void* b, size_t n) {
    const unsigned char* p1 = a;
    const unsigned char* p2 = b;

    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }

        p1++;
        p2++;
    }

    return 0;
}