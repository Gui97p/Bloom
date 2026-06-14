#include <bin/terminal/terminal.h>
#include "../builtins.h"

int cmdHelp(terminal_t* term, int argc, char** argv) {
    termWrite(term, builtins[0].name);
    for (int i = 1; i < builtinsCount; i++) {
        termPrintf(term, " %s", builtins[i].name);
    }

    return 0;
}
