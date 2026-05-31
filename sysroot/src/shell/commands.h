#pragma once

int boot(int argc, char** argv);

typedef int (*command_func_t)(int argc, char** argv);

typedef struct {
    const char* name;
    command_func_t func;
} command_t;

extern command_t commands[];
extern const int commandCount;