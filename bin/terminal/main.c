#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <bin/terminal/terminal.h>
#include <bin/shell/shell.h>
#include <glib/glib.h>
#include <glib/fonts/font.h>

#include "readline.h"

static termCell_t terminalBuffer[60][120];

static void terminalScroll(terminal_t* term) {
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
}

void terminalMain(gfxContext_t* ctx) {
    terminal_t term = {0};
    term.screen = terminalBuffer;
    term.cols = 120;
    term.rows = 49;
    term.cursorX = 0;
    term.cursorY = 0;
    term.gfx = ctx;

    terminalWriteString(&term, "Welcome to BloomOS!\n");

    while (1) {    
        terminalWriteString(&term, "user@host:~ $ ");
        char line[120];
        terminalFlush(&term);

        readline(&term, line, 120);
        if (line[0] == '\0') continue;

        runCommand(&term, line);

        terminalPutChar(&term, '\n');
    }
}

void terminalPutChar(terminal_t* term, char c) {
    switch (c) {
        case '\n': {
            term->cursorY++;
            term->cursorX = 0;
            if (term->cursorY >= term->rows) {
                terminalScroll(term);
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
                term->screen[term->cursorY][term->cursorX].ch = c;
                term->screen[term->cursorY][term->cursorX].fg = 0xFFFFFF;
                term->screen[term->cursorY][term->cursorX++].bg = 0x000000;
                term->screen[term->cursorY][term->cursorX].ch = '\0';
            }
            break;
        }
    }
}

void terminalWriteString(terminal_t* term, char* str) {
    while (*str) {
        terminalPutChar(term, *str);
        str++;
    }
}

void terminalFlush(terminal_t* term) {
    gfxBeginFrame(term->gfx);
    
    fillRect(term->gfx, 0, 0, term->gfx->width, term->gfx->height, 0x000000);

    for (int row = 0; row < term->rows; row++) {
        for (int col = 0; col < term->cols; col++) {
            char c = term->screen[row][col].ch;

            if (c == '\0')
                continue;

            drawChar(
                term->gfx,
                &font8x16,
                10 + col * 8,
                row * 16,
                c,
                term->screen[row][col].fg
            );
        }
    }

    gfxEndFrame(term->gfx);
}

void terminalClear(terminal_t* term) {
    memset(
        term->screen,
        0,
        term->rows * term->cols * sizeof(termCell_t)
    );

    term->cursorX = 0;
    term->cursorY = 0;
}