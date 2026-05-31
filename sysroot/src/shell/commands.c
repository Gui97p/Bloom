#include <shell/commands.h>

int cmdHelp(int argc, char** argv);
int cmdEcho(int argc, char** argv);
int cmdExit(int argc, char** argv);
int cmdClear(int argc, char** argv);
int cmdVersion(int argc, char** argv);
int cmdUname(int argc, char** argv);

int boot(int argc, char** argv);

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