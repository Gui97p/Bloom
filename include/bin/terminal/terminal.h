#pragma once

#include <glib/gfx/context.h>
#include <glib/fonts/font.h>

typedef struct {
    char ch;

    uint32_t fg;
    uint32_t bg;

    font_t* font;
    uint8_t flags;
} termCell_t;

typedef struct {
    termCell_t (*screen)[120];

    int cursorX;
    int cursorY;

    int rows;
    int cols;

    uint32_t currentFg;
    uint32_t currentBg;

    font_t* font;

    gfxContext_t* gfx;
} terminal_t;

void termMain(gfxContext_t* ctx);
void termSetFont(terminal_t* term, font_t* font);
void termSetColor(terminal_t* term, uint32_t fg, uint32_t bg);
void termPutChar(terminal_t* term, char c);
void termPutCharEx(terminal_t* term, char c, uint32_t fg, uint32_t bg);
void termWrite(terminal_t* term, char* str);
void termWriteEx(terminal_t* term, char* str, uint32_t fg, uint32_t bg);
void termPrintf(terminal_t* term, const char* fmt, ...);
void termFlush(terminal_t* term);
void termClear(terminal_t* term);