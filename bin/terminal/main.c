#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>

#include <bin/terminal/terminal.h>
#include <bin/shell/shell.h>
#include <glib/gfx/context.h>
#include <glib/gfx/rect.h>
#include <glib/fonts/font.h>

#include "readline.h"

static termCell_t terminalBuffer[60][120];
static termCell_t previous[60][120];

static void termScroll(terminal_t* term) {
    for (int y = 1; y < term->rows; y++) {
        memcpy(
            term->screen[y - 1],
            term->screen[y],
            sizeof(term->screen[y])
        );
    }

    memset(
        term->screen[term->rows - 1],
        0,
        sizeof(term->screen[0])
    );

    term->cursorY = term->rows - 1;

    memset(previous, 0xFF, sizeof(previous));
}

void termMain(gfxContext_t* ctx) {
    terminal_t term = {0};
    term.screen = terminalBuffer;
    term.cols = 120;
    term.rows = 49;
    term.cursorX = 0;
    term.cursorY = 0;
    term.currentFg = 0xAAAAAA;
    term.currentBg = 0x1A001A;
    term.font = &font8x16;
    term.gfx = ctx;
    
    memset(terminalBuffer, 0, sizeof(terminalBuffer));
    
    termClear(&term);

    gfxBeginFrame(ctx);
    fillRect(ctx, 0, 0, ctx->width, ctx->height, term.currentBg);
    gfxEndFrame(ctx);

    memset(previous, 0xFF, sizeof(previous));
    
    termWriteEx(&term, "Welcome to BloomOS!\n", 0xFF884D, term.currentBg);

    while (1) {
        termWriteEx(&term, "user", 0x1CB51C, term.currentBg);
        termPutChar(&term, '@');
        termWriteEx(&term, "host", 0x1CB51C, term.currentBg);
        termPutChar(&term, ':');
        termPutCharEx(&term, '~', 0x008ADE, term.currentBg);
        termWrite(&term, " $ ");
        
        char line[120];
        termFlush(&term);

        readline(&term, line, 120);
        if (line[0] == '\0') continue;

        runCommand(&term, line);

        termPutChar(&term, '\n');
    }
}

void termSetColor(terminal_t* term, uint32_t fg, uint32_t bg) {
    term->currentFg = fg;
    term->currentBg = bg;
}

void termSetFont(terminal_t* term, font_t* font) {
    term->font = font;
}

void termPutCharEx(terminal_t* term, char c, uint32_t fg, uint32_t bg) {
    switch (c) {
        case '\n': {
            term->cursorY++;
            term->cursorX = 0;
            if (term->cursorY >= term->rows) {
                termScroll(term);
            }

            break;
        }
        
        case '\b': {
            if (term->cursorX > 0) {
                term->cursorX--;
                term->screen[term->cursorY][term->cursorX].ch = '\0';
            }
            break;
        }

        default: {
            if (term->cursorX < term->cols - 1) {
                termCell_t* cell =
                    &term->screen[term->cursorY][term->cursorX];

                cell->ch = c;
                cell->fg = fg;
                cell->bg = bg;

                term->cursorX++;

                if (term->cursorX < term->cols) {
                    term->screen[term->cursorY][term->cursorX].ch = '\0';
                }
            }
            break;
        }
    }
}

void termPutChar(terminal_t* term, char c) {
    termPutCharEx(term, c, term->currentFg, term->currentBg);
}

void termWriteEx(terminal_t* term, char* str, uint32_t fg, uint32_t bg) {
    while (*str) {
        termPutCharEx(term, *str, fg, bg);
        str++;
    }
}

void termWrite(terminal_t* term, char* str) {
    while (*str) {
        termPutChar(term, *str);
        str++;
    }
}

static inline bool termCellEqual(termCell_t a, termCell_t b) {
    return a.ch == b.ch &&
           a.fg == b.fg &&
           a.bg == b.bg;
}

void termRenderer(terminal_t* term) {
    for (int row = 0; row < term->rows; row++) {
        for (int col = 0; col < term->cols; col++) {
            termCell_t cell = term->screen[row][col];

            if (termCellEqual(cell, previous[row][col])) continue;

            int x = 10 + col * 8;
            int y = row * 16;

            fillRect(
                term->gfx,
                x,
                y,
                term->font->width,
                term->font->height,
                cell.bg
            );

            if (cell.ch != '\0') {
                drawChar(
                    term->gfx,
                    term->font,
                    x,
                    y,
                    cell.ch,
                    term->screen[row][col].fg
                );
            }

            previous[row][col] = cell;
                
        }
    }
}

void termPrintf(terminal_t* term, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            termPutChar(term, *fmt++);
            continue;
        }

        fmt++;

        switch (*fmt) {
            case '%':
                termPutChar(term, '%');
                break;

            case 'c': {
                char c = (char)va_arg(args, int);
                termPutChar(term, c);
                break;
            }

            case 's': {
                char* str = va_arg(args, char*);
                termWrite(term, str ? str : "(null)");
                break;
            }

            case 'i':
            case 'd': {
                int n = va_arg(args, int);

                char buf[16];
                itoa(n, buf, 10);

                termWrite(term, buf);
                break;
            }

            case 'u': {
                unsigned n = va_arg(args, unsigned);

                char buf[16];
                utoa(n, buf, 10);

                termWrite(term, buf);
                break;
            }

            case 'x': {
                unsigned n = va_arg(args, unsigned);

                char buf[16];
                utoa(n, buf, 16);

                termWrite(term, buf);
                break;
            }

            case 'p': {
                uintptr_t ptr = va_arg(args, uintptr_t);

                termWrite(term, "0x");

                char buf[32];
                utoa(ptr, buf, 16);

                termWrite(term, buf);
                break;
            }
        }

        fmt++;
    }

    va_end(args);
}

void termFlush(terminal_t* term) {
    gfxBeginFrame(term->gfx);
    
    termRenderer(term);

    gfxEndFrame(term->gfx);
}

void termClear(terminal_t* term) {
    for (int y = 0; y < term->rows; y++) {
        for (int x = 0; x < term->cols; x++) {
            term->screen[y][x].ch = '\0';
            term->screen[y][x].fg = term->currentFg;
            term->screen[y][x].bg = term->currentBg;
        }
    }

    memset(previous, 0xFF, sizeof(previous));

    term->cursorX = 0;
    term->cursorY = 0;
}