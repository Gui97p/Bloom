unsigned long strtoul(const char *nptr, char **endptr, int base) {
    const char *s = nptr;
    unsigned long result = 0;
    int digit;

    while (*s == ' '  ||
           *s == '\t' ||
           *s == '\n' ||
           *s == '\r' ||
           *s == '\f' ||
           *s == '\v') {
        s++;
    }

    if (*s == '+') {
        s++;
    }

    if (base == 0) {
        if (*s == '0') {
            if (s[1] == 'x' || s[1] == 'X') {
                base = 16;
                s += 2;
            } else {
                base = 8;
                s++;
            }
        } else {
            base = 10;
        }
    }
    else if (base == 16) {
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            s += 2;
        }
    }

    const char *start = s;

    while (*s) {
        if (*s >= '0' && *s <= '9') {
            digit = *s - '0';
        }
        else if (*s >= 'a' && *s <= 'z') {
            digit = *s - 'a' + 10;
        }
        else if (*s >= 'A' && *s <= 'Z') {
            digit = *s - 'A' + 10;
        }
        else {
            break;
        }

        if (digit >= base) {
            break;
        }

        result = result * base + digit;
        s++;
    }

    if (endptr) {
        *endptr = (char *)(s == start ? nptr : s);
    }

    return result;
}
