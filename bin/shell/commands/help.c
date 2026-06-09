#include <bin/terminal/terminal.h>
#include "../commands.h"

int cmdHelp(terminal_t* term, int argc, char** argv) {
    terminalWriteString(term, commands[0].name);
    for (int i = 1; i < commandCount; i++) {
        terminalPutChar(term, ' ');
        terminalWriteString(term, commands[i].name);
    }

    return 0;
}
