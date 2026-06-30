#include <stdio.h>

int cmdCp(int argc, char** argv) {
    if (argc < 3) {
        printf("cp: invalid input.");
        return -1;
    }

    FILE* src = fopen(argv[1], "r");
    FILE* dest = fopen(argv[2], "w");

    if (!src) {
        printf("cp: file not found.");
        return -1;
    }

    if (!dest) {
        printf("cp: error on creating file.");
        return -1;
    }

    char buf[1024];
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf)-1, src)) > 0) {
        fwrite(buf, 1, n, dest);
    }

    fclose(src);
    fclose(dest);

    printf(buf);

    return 0;
}
