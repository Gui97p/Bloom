#include <bin/terminal/terminal.h>
#include "../commands.h"

int cmdHelp(terminal_t* term, int argc, char** argv) {
    termWrite(term, commands[0].name);
    for (int i = 1; i < commandCount; i++) {
        termPrintf(term, " %s", commands[i].name);
    }

    return 0;
}
