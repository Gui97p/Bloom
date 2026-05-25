char * strcpy(char *restrict to, const char *restrict from) {
    int i = 0;

    while (from[i] != '\0') {
        to[i] = from[i];
        i++;
    }

    to[i] = '\0';

    return to;
}
