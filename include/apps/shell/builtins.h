#pragma once

#include <apps/terminal/terminal.h>

typedef int (*command_func_t)(int argc, char** argv);

typedef struct {
    const char* name;
    command_func_t func;
} builtin_t;

extern builtin_t builtins[];
extern const int builtinsCount;
