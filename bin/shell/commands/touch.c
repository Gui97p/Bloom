#include <stdio.h>

int cmdTouch(int argc, char** argv) {
    if (argc < 2) {
        printf("touch: invalid input.");
        return -1;
    }

    FILE* f = fopen(argv[1], "w+");

    if (!f) {
        printf("touch: error on creating file.");
        return -1;
    }

    fclose(f);

    return 0;
}