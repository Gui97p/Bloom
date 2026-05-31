#include <stdio.h>
#include <string.h>
#include <shell/commands.h>

int cmdHelp(int argc, char** argv);
static command_t commands[] = {
    { "help",  cmdHelp  }
};

static const int commandCount = 
    sizeof(commands) / sizeof(commands[0]);

void shell() {
    char line[256];

    while (1) {
        printf("> ");
        readline(line, sizeof(line));

        char* argv[16];
        int argc = 0;

        char* token = strtok(line, " ");

        while (token && argc < 16) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        for (int i = 0; i < commandCount; i++) {
            if (strcmp(argv[0], commands[i].name) == 0) {
                commands[i].func(argc, argv);
            }
        }
    }
}