#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "commands.h"
#include "readline.h"
#include "parser.h"

#define MAX_ARGS 16

void shell(int argc, char** argv) {
    char line[256];
    
    boot(argc, argv);
    
    while (1) {
        printf("> ");
        fflush(stdout);

        char* argv[16];
        
        readline(line, sizeof(line));
        if (line[0] == '\0') continue;
        
        int argc = parse(line, argv, 16);

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
