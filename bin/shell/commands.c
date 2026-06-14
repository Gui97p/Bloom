#include <bin/terminal/terminal.h>
#include "commands.h"

int cmdHelp(terminal_t* term, int argc, char** argv);
int cmdEcho(terminal_t* term, int argc, char** argv);
int cmdExit(terminal_t* term, int argc, char** argv);
int cmdClear(terminal_t* term, int argc, char** argv);
int cmdVersion(terminal_t* term, int argc, char** argv);
int cmdUname(terminal_t* term, int argc, char** argv);
int cmdCat(terminal_t* term, int argc, char** argv);
int cmdTouch(terminal_t* term, int argc, char** argv);
int cmdEchofile(terminal_t* term, int argc, char** argv);
int cmdCp(terminal_t* term, int argc, char** argv);
int cmdLs(terminal_t* term, int argc, char** argv);

command_t commands[] = {
    { "help", cmdHelp },
    { "echo", cmdEcho },
    { "exit", cmdExit },
    { "clear", cmdClear },
    { "version", cmdVersion },
    { "uname", cmdUname },
    { "cat", cmdCat },
    { "touch", cmdTouch },
    { "echofile", cmdEchofile },
    { "cp", cmdCp },
    { "ls", cmdLs }
};

const int commandCount =
    sizeof(commands) / sizeof(commands[0]);