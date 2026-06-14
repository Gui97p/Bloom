#include <stdio.h>
#include <string.h>

#include <bin/terminal/terminal.h>

#include "builtins.h"
#include "parser.h"
#include "readline.h"

#define MAX_ARGS 16

int runBuiltin(terminal_t* term, int argc, char** argv) {
    for (int i = 0; i < builtinsCount; i++) {
        if (strcmp(argv[0], builtins[i].name) == 0) {
            builtins[i].func(term, argc, argv);
            return 1;
        }
    }

    
    return 0;
}

void buildProgramPath(const char* cmd, char* out) {
    strcpy(out, "/bin/");
    strcat(out, cmd);
    strcat(out, ".elf");
}

int runExternal(terminal_t* term, int argc, char** argv) {
    char path[256];
    buildProgramPath(argv[0], path);

    termPrintf(term, "%s: Command not found", argv[0]);

    return -1;
}

int shellExecute(terminal_t* term, char* line) {
    char* argv[MAX_ARGS];
    int argc = parse(line, argv, MAX_ARGS);
    
    if (runBuiltin(term, argc, argv))
        return 0;
    
    return runExternal(term, argc, argv);
}

void shellMain(terminal_t* term) {
    termWriteEx(term, "Welcome to BloomOS!\n", 0xFF884D, term->currentBg);

    while (1) {
        termWriteEx(term, "user@bloom", 0x1CB51C, term->currentBg);

        termPutChar(term, ':');
        termPutCharEx(term, '~', 0x008ADE, term->currentBg);
        termWrite(term, " $ ");
        
        char line[120];
        termFlush(term);

        readline(term, line, 120);
        if (line[0] == '\0') continue;

        shellExecute(term, line);

        termPutChar(term, '\n');
    }
}
