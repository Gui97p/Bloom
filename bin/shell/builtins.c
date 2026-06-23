#include <bin/terminal/terminal.h>
#include <bin/shell/builtins.h>

int cmdHelp(int argc, char** argv);
int cmdEcho(int argc, char** argv);
int cmdExit(int argc, char** argv);
int cmdClear(int argc, char** argv);
int cmdVersion(int argc, char** argv);
int cmdUname(int argc, char** argv);
int cmdCat(int argc, char** argv);
int cmdTouch(int argc, char** argv);
int cmdEchofile(int argc, char** argv);
int cmdCp(int argc, char** argv);
int cmdLs(int argc, char** argv);
int cmdReboot(int argc, char** argv);
int cmdMkdir(int argc, char** argv);

builtin_t builtins[] = {
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
    { "ls", cmdLs },
    { "reboot", cmdReboot },
    { "mkdir", cmdMkdir }
};

const int builtinsCount =
    sizeof(builtins) / sizeof(builtins[0]);
