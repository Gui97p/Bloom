#include <bin/terminal/terminal.h>

int cmdEcho(terminal_t* term, int argc, char** argv) {
    if (argc <= 1) {
        termPutChar(term, '\n');
        return 0;
    }

    termWrite(term, argv[1]);

    for (int i = 2; i < argc; i++) {
        termPrintf(term, " %s", argv[i]);
    }

    return 0;
}