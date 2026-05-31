#include <stdio.h>

int cmdEcho(int argc, char** argv) {
    if (argc <= 1) {
        putchar('\n');
        return 0;
    }

    printf("%s", argv[1]);

    for (int i = 2; i < argc; i++) {
        printf(" %s", argv[i]);
    }

    return 0;
}