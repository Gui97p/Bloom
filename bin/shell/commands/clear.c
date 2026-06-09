#include <bin/terminal/terminal.h>

int cmdClear(terminal_t* term, int argc, char** argv) {
    (void)argc;
    (void)argv;

    terminalClear(term);
    
    return 0;
}