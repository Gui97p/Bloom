#pragma once

#include <glib/glib.h>

typedef struct {
    char screen[60][120];

    int cursorX;
    int cursorY;

    int rows;
    int cols;

    gfxContext_t* gfx;
} terminal_t;

void terminalMain(gfxContext_t* ctx);
void terminalPutChar(terminal_t* term, char c);
void terminalWriteString(terminal_t* term, char* str);
void terminalFlush(terminal_t* term);