#include <bin/terminal/terminal.h>
#include "commands.h"

int cmdHelp(terminal_t* term, int argc, char** argv);
int cmdEcho(terminal_t* term, int argc, char** argv);
int cmdExit(terminal_t* term, int argc, char** argv);
int cmdClear(terminal_t* term, int argc, char** argv);
int cmdVersion(terminal_t* term, int argc, char** argv);
int cmdUname(terminal_t* term, int argc, char** argv);

command_t commands[] = {
    { "help", cmdHelp },
    { "echo", cmdEcho },
    { "exit", cmdExit },
    { "clear", cmdClear },
    { "version", cmdVersion },
    { "uname", cmdUname },
};

const int commandCount =
    sizeof(commands) / sizeof(commands[0]);