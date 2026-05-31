#include <shell/commands.h>

int cmdHelp(int argc, char** argv);
int cmdEcho(int argc, char** argv);
int cmdExit(int argc, char** argv);

int boot(int argc, char** argv);

command_t commands[] = {
    { "help", cmdHelp },
    { "echo", cmdEcho },
    { "exit", cmdExit }
};

const int commandCount =
    sizeof(commands) / sizeof(commands[0]);