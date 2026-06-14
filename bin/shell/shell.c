#include <stdio.h>
#include <string.h>

#include <bin/terminal/terminal.h>
#include <bloom/theme.h>

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

void shellMain(terminal_t* term, bloomTheme_t* theme) {
    termWriteEx(term, "Welcome to BloomOS!\n", theme->accent_gold, term->currentBg);

    while (1) {
        termWriteEx(term, "root", theme->accent_bright, theme->bg_deep);
        termWriteEx(term, "@",    theme->fg_dim,        theme->bg_deep);
        termWriteEx(term, "bloom",theme->accent_purple, theme->bg_deep);
        termWriteEx(term, ":~$ ", theme->fg_dim,        theme->bg_deep);
        
        char line[120];
        termFlush(term);

        readline(term, line, 120);
        if (line[0] == '\0') continue;

        shellExecute(term, line);

        termPutChar(term, '\n');
    }
}
