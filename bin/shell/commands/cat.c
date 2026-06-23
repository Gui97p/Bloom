#include <stdio.h>
#include <string.h>

int cmdCat(int argc, char** argv) {
    if (argc < 2) {
        printf("cat: invalid input.");
        return -1;
    }

    char path[256];

    if (argv[1][0] == '/') {
        strncpy(path, argv[1], sizeof(path) - 1);
        path[sizeof(path) - 1] = '\0';
    } else {
        snprintf(path, sizeof(path), "/%s", argv[1]);
    }

    FILE* f = fopen(path, "r");

    if (!f) {
        printf("cat: file not found.");
        return -1;
    }

    char buf[1024];
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf)-1, f)) > 0) {
        buf[n] = '\0';
        printf(buf);
    }

    fclose(f);

    printf(buf);

    return 0;
}
