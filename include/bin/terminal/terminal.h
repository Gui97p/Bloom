#pragma once

#include <glib/glib.h>

typedef struct {
    char ch;
    uint32_t fg;
    uint32_t bg;
} termCell_t;

typedef struct {
    termCell_t (*screen)[120];

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
void terminalClear(terminal_t* term);