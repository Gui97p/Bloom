#include <bin/terminal/terminal.h>
#include <stdio.h>

int cmdCat(terminal_t* term, int argc, char** argv) {
    if (argc < 2) {
        termWrite(term, "cat: Invalid input.");
        return -1;
    }

    FILE* f = fopen(argv[1], "r");

    if (!f) {
        termWrite(term, "cat: file not found.");
        return -1;
    }

    char buf[1024];
    size_t n;

    while ((n = fread(buf, 1, sizeof(buf)-1, f)) > 0) {
        buf[n] = '\0';
        termWrite(term, buf);
    }

    fclose(f);

    termWrite(term, buf);

    return 0;
}
