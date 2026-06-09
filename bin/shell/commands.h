#pragma once

#include <bin/terminal/terminal.h>

typedef int (*command_func_t)(terminal_t* term, int argc, char** argv);

typedef struct {
    const char* name;
    command_func_t func;
} command_t;

extern command_t commands[];
extern const int commandCount;