#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <bin/terminal/terminal.h>
#include <bin/shell/shell.h>
#include <glib/glib.h>
#include "readline.h"

void terminalMain(gfxContext_t* ctx) {
    terminal_t term = {0};
    term.cols = 120;
    term.rows = 60;
    term.cursorX = 0;
    term.cursorY = 0;
    term.gfx = ctx;

    terminalWriteString(&term, "Welcome to BloomOS!\n");

    while (1) {
        terminalWriteString(&term, "> ");
        char line[110];
        terminalFlush(&term);

        readline(&term, line, 110);
        if (line[0] == '\0') continue;

        runCommand(&term, line);

        terminalPutChar(&term, '\n');
    }
}

void terminalPutChar(terminal_t* term, char c) {
    switch (c) {
        case '\n':
            if (term->cursorY < term->rows - 1) {
                term->cursorY++;
            }
            
            term->cursorX = 0;
            break;
        
        case '\b':
            if (term->cursorX > 0) {
                term->cursorX--;
                term->screen[term->cursorY][term->cursorX] = '\0';
            }
            break;

        default:
            if (term->cursorX < term->cols - 1) {
                term->screen[term->cursorY][term->cursorX++] = c;
                term->screen[term->cursorY][term->cursorX] = '\0';
            }
            break;
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
        drawString(term->gfx, 10, row * 16, term->screen[row], 0xFFFFFF);
    }

    gfxEndFrame(term->gfx);
}
