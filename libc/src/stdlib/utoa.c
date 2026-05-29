#include <stdint.h>

char *utoa(uint64_t value, char *buf, int base) {
    char tmp[64];
    char *p = tmp;
    char *out = buf;

    if (base < 2 || base > 36)
        goto end;

    do {
        uint64_t digit = value % base;
        *p++ = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        value /= base;
    } while (value > 0);

    while (p > tmp)
        *out++ = *--p;

end:
    *out = '\0';
    return buf;
}