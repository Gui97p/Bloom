#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    char* name;
    char* desc;
} cmd_t;

static const cmd_t commands[] = {
    {.name = "echo", .desc = "Print text to terminal"},
    {.name = "exit", .desc = "Halt userspace and return to kernel"},
    {.name = "clear", .desc = "Clear the screen"},
    {.name = "version", .desc = "Print system version"},
    {.name = "uname", .desc = "Print system information"},
    {.name = "cat", .desc = "Print file content to terminal"},
    {.name = "touch", .desc = "Creates new file"},
    {.name = "echofile", .desc = "Print text to file"},
    {.name = "ls", .desc = "Print directory contents"}
};

static void writeCmd(cmd_t cmd) {
    printf("\033[305m%s", cmd.name);
    for (int i = 0; i < (10 - strlen(cmd.name)); i++) putchar(' ');
    printf("\033[300m%s\033[0m", cmd.desc);
}

int cmdHelp(int argc, char** argv) {
    printf("\n   \033[303mBuilt-in commands:\n   \033[301m---------------------------------------------");
    
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        printf("\n   ");
        writeCmd(commands[i]);
    }

    putchar('\n');

    return 0;
}
