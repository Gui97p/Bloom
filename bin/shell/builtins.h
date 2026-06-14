#pragma once

#include <bin/terminal/terminal.h>

typedef int (*command_func_t)(terminal_t* term, int argc, char** argv);

typedef struct {
    const char* name;
    command_func_t func;
} builtin_t;

extern builtin_t builtins[];
extern const int builtinsCount;
