#pragma once

#include <stdbool.h>
#include <glib/gfx/context.h>
#include <glib/fonts/font.h>
#include <bloom/theme.h>

#define CELL(t, y, x) ((t)->screen[(y) * (t)->cols + (x)])
#define PCELL(t, y, x) ((t)->previous[(y) * (t)->cols + (x)])

typedef enum {
    ANSI_NORMAL,
    ANSI_ESC,
    ANSI_CSI
} ansiState_t;

typedef struct {
    char ch;

    uint32_t fg;
    uint32_t bg;

    font_t* font;
    uint8_t flags;
} termCell_t;

typedef struct {
    termCell_t* screen;
    termCell_t* previous;

    int cursorX;
    int cursorY;

    int rows;
    int cols;

    font_t* font;

    gfxSurface_t* surface;
    gfxSurface_t viewport;

    bloomTheme_t* theme;
    uint32_t currentFg;
    uint32_t currentBg;

    ansiState_t ansiState;
    char ansiBuf[16];
    int ansiLen;

    int cursorCounter;
    bool cursorVisible;
} terminal_t;

void termInit(terminal_t* term, gfxSurface_t* surface, bloomTheme_t* theme);
void termSetFont(terminal_t* term, font_t* font);
void termPutChar(terminal_t* term, char c, uint32_t fg, uint32_t bg);
void termWrite(terminal_t* term, char* str);
void termFlush(terminal_t* term);
void termClear(terminal_t* term);
