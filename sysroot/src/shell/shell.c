#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <shell/commands.h>
#include "readline.h"

#define MAX_ARGS 16

void shell(int argc, char** argv) {
    char line[256];

    boot(argc, argv);

    while (1) {
        printf("> ");
        fflush(stdout);
        readline(line, sizeof(line));

        char* argv[MAX_ARGS];
        int argc = 0;

        char* token = strtok(line, " ");

        while (token && argc < 16) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        bool found = false;
        for (int i = 0; i < commandCount; i++) {
            if (strcmp(argv[0], commands[i].name) == 0) {
                commands[i].func(argc, argv);
                found = true;
                break;
            }
        }
        if (!found) {
            printf("%s: Command not found", argv[0]);
        }

        putchar('\n');
    }
}
