#include <stdio.h>
#include <string.h>
#include <bin/terminal/terminal.h>

int cmdEchofile(terminal_t* term, int argc, char** argv) {
    if (argc < 3) {
        termWrite(term, "echofile: Invalid input.");
        return -1;
    }

    FILE* f = fopen(argv[1], "w");

    if (!f) {
        termWrite(term, "echofile: error on opening file.");
        return -1;
    }

    fwrite(argv[2], 1, strlen(argv[2]), f);
    for (int i = 3; i < argc; i++) {
        fputc(' ', f);
        fwrite(argv[i], 1, strlen(argv[i]), f);
    }

    fclose(f);

    return 0;
}
