#include <stdio.h>
#include <shell/commands.h>

int cmdHelp(int argc, char** argv) {
    printf("%s", commands[0].name);
    for (int i = 1; i < commandCount; i++) {
        printf(" %s", commands[i].name);
    }

    return 0;
}