char *itoa(int value, char *str, int base) {
    if (base < 2 || base > 36) {
        str[0] = '\0';
        return str;
    }

    char *ptr = str;
    char *ptr1 = str;
    char tmp;

    int negative = 0;

    if (value < 0 && base == 10) {
        negative = 1;
        value = -value;
    }

    do {
        int digit = value % base;

        *ptr++ =
            (digit < 10)
                ? '0' + digit
                : 'a' + (digit - 10);

        value /= base;

    } while (value);

    if (negative) {
        *ptr++ = '-';
    }

    *ptr = '\0';

    ptr--;

    while (ptr1 < ptr) {
        tmp = *ptr;
        *ptr = *ptr1;
        *ptr1 = tmp;

        ptr--;
        ptr1++;
    }

    return str;
}