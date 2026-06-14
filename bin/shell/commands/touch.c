#include <bin/terminal/terminal.h>
#include <stdio.h>

int cmdTouch(terminal_t* term, int argc, char** argv) {
    if (argc < 2) {
        termWrite(term, "touch: Invalid input.");
        return -1;
    }

    FILE* f = fopen(argv[1], "w+");

    if (!f) {
        termWrite(term, "touch: error on creating file.");
        return -1;
    }

    fclose(f);

    return 0;
}