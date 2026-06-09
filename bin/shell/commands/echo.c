#include <bin/terminal/terminal.h>

int cmdEcho(terminal_t* term, int argc, char** argv) {
    if (argc <= 1) {
        terminalPutChar(term, '\n');
        return 0;
    }

    terminalWriteString(term, argv[1]);

    for (int i = 2; i < argc; i++) {
        terminalPutChar(term, ' ');
        terminalWriteString(term, argv[i]);
    }

    return 0;
}