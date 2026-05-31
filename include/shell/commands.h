#pragma once

typedef int (*command_func_t)(int argc, char** argv);

typedef struct {
    const char* name;
    command_func_t func;
} command_t;