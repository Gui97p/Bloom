char *itoa(int value, char *buf, int base) {
    char tmp[32];
    char *p = tmp;
    char *out = buf;
    int negative = 0;

    if (base < 2 || base > 36)
        goto end;

    if (value < 0 && base == 10) {
        negative = 1;
        value = -value;
    }

    do {
        int digit = (unsigned int)value % base;
        *p++ = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        value = (unsigned int)value / base;
    } while (value > 0);

    if (negative)
        *p++ = '-';

    while (p > tmp)
        *out++ = *--p;

end:
    *out = '\0';
    return buf;
}
