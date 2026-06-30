#pragma once

#include <stdbool.h>
#include <apps/terminal/terminal.h>
#include <glib/input/keyboard.h>

#define HISTORY_SIZE 32
#define MAX_CMD_LEN 120

typedef struct {
    char line[120];
    size_t pos;

    char tmp[MAX_CMD_LEN];

    int historyPos;
} readline_t;

void readlineInit(readline_t* rl);
bool readlineFeed(readline_t* rl, terminal_t* term, keyEvent_t* ev);
