#include <stdio.h>
#include <string.h>

#include <bin/shell/builtins.h>
#include <bin/terminal/terminal.h>
#include <bin/console/readline.h>
#include <bloom/theme.h>
#include <bloom/debug.h>

#include "parser.h"

#define MAX_ARGS 16

int runBuiltin(int argc, char** argv) {
    DPRINTF("[CONSOLE] Searching for Builtin\n");

    for (int i = 0; i < builtinsCount; i++) {
        if (strcmp(argv[0], builtins[i].name) == 0) {
            builtins[i].func(argc, argv);
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

int runExternal(int argc, char** argv) {
    DPRINTF("[SHELL] Searching for External\n");
    
    char path[256];
    buildProgramPath(argv[0], path);

    printf("%s: Command not found", argv[0]);

    return -1;
}

int shellExecute(terminal_t* term, char* line) {
    DPRINTF("[SHELL] Executing command line: %s\n", line);

    char* argv[MAX_ARGS];
    int argc = parse(line, argv, MAX_ARGS);
    
    if (runBuiltin(argc, argv))
        return 0;
    
    return runExternal(argc, argv);
}

void shellPrompt() {
    printf(
        "\033[303mroot"
        "\033[301m@"
        "\033[302mbloom"
        "\033[301m:~$\033[0m "
    );
}
