#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <bin/terminal/terminal.h>
#include "commands.h"
#include "parser.h"

#define MAX_ARGS 16

bool runCommand(terminal_t* term, char* line) {
    char* argv[MAX_ARGS];
    int argc = parse(line, argv, MAX_ARGS);

    for (int i = 0; i < commandCount; i++) {
        if (strcmp(argv[0], commands[i].name) == 0) {
            commands[i].func(term, argc, argv);
            return true;
        }
    }

    termPrintf(term, "%s: Command not found", argv[0]);

    return false;
}
