#include <stdio.h>
#include <bin/terminal/terminal.h>

int cmdCp(terminal_t* term, int argc, char** argv) {
    if (argc < 3) {
        termWrite(term, "cp: Invalid input.");
        return -1;
    }

    FILE* src = fopen(argv[1], "r");
    FILE* dest = fopen(argv[2], "w");

    if (!src) {
        termWrite(term, "cat: file not found.");
        return -1;
    }

    if (!dest) {
        termWrite(term, "cat: error on creating file.");
        return -1;
    }

    char buf[1024];
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf)-1, src)) > 0) {
        fwrite(buf, 1, n, dest);
    }

    fclose(src);
    fclose(dest);

    termWrite(term, buf);

    return 0;
}
