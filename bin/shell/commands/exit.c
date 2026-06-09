#include <bin/terminal/terminal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int cmdExit(terminal_t* term, int argc, char** argv) {
    int code = 0;

    if (argc > 1) {
        code = atoi(argv[1]);
    }

    fflush(stdout);
    fflush(stderr);
    
    exit(code);
}