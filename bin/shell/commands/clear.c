#include <bin/terminal/terminal.h>

int cmdClear(terminal_t* term, int argc, char** argv) {
    (void)argc;
    (void)argv;

    for (int i = 0; i < 40; i++)
        terminalPutChar(term, '\n');
    
    return 0;
}