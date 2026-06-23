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
#include <bloom/debug.h>

#include "ansi.h"
#include "renderer.h"
#include "tools.h"

void termInit(terminal_t* term, gfxSurface_t* surface, bloomTheme_t* theme) {
    term->surface = surface;

    gfxCreateSurface(&term->viewport, surface->width - 32, surface->height);

    term->font = &font16x32;

    term->cols = term->viewport.width / term->font->width;
    term->rows = term->viewport.height / term->font->height;

    term->cursorX = 0;
    term->cursorY = 0;

    term->theme = theme;
    term->currentFg = theme->fg_primary;
    term->currentBg = theme->bg_deep;

    term->ansiState = ANSI_NORMAL;
    term->ansiLen = 0;

    term->cursorCounter = 0;
    term->cursorVisible = true;
    
    memset(term->ansiBuf, 0, sizeof(term->ansiBuf));

    size_t size = term->rows * term->cols * sizeof(termCell_t);

    term->screen = malloc(size);
    term->previous = malloc(size);

    memset(term->screen, 0, size);
    memset(term->previous, 0, size);
    termClear(term);
    
    gfxFillRect(surface, 0, 0, surface->width, surface->height, theme->bg_deep);
    
    memset(term->previous, 0xFF, size);
}


void termSetFont(terminal_t* term, font_t* font) {
    term->font = font;
}

void termPutChar(terminal_t* term, char c, uint32_t fg, uint32_t bg) {
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
                CELL(term, term->cursorY, term->cursorX).ch = '\0';
            
            }
            break;
        }

        default: {
            if (term->cursorX >= term->cols) {
                term->cursorX = 0;
                term->cursorY++;

                if (term->cursorY >= term->rows)
                    termScroll(term);
            }
            ASSERT(term->cursorX >= 0);
            ASSERT(term->cursorX < term->cols);
            
            ASSERT(term->cursorY >= 0);
            ASSERT(term->cursorY < term->rows);
            
            termCell_t* cell = &CELL(term, term->cursorY, term->cursorX);

            cell->ch = c;
            cell->fg = fg;
            cell->bg = bg;

            term->cursorX++;

            break;
        }
    }
}

void termFeed(terminal_t* term, char c) {
    switch (term->ansiState) {
        case ANSI_NORMAL: {
            if (c == '\033') {
                term->ansiState = ANSI_ESC;
            } else {
                termPutChar(
                    term,
                    c,
                    term->currentFg,
                    term->currentBg
                );
            }
            break;
        }

        case ANSI_ESC: {
            if (c == '[') {
                term->ansiState = ANSI_CSI;
                term->ansiLen = 0;
            } else {
                termPutChar(
                    term,
                    '\033',
                    term->currentFg,
                    term->currentBg
                );

                termPutChar(
                    term,
                    c,
                    term->currentFg,
                    term->currentBg
                );

                term->ansiState = ANSI_NORMAL;
            }
            break;
        }

        case ANSI_CSI: {
            if ((c >= '0' && c <= '9') || c == ';') {
                if (term->ansiLen < sizeof(term->ansiBuf) - 1) {
                    term->ansiBuf[term->ansiLen++] = c;
                }
            } else {
                term->ansiBuf[term->ansiLen] = '\0';

                ansiExecute(
                    term,
                    term->ansiBuf,
                    c
                );

                term->ansiState = ANSI_NORMAL;
                term->ansiLen = 0;
            }

            break;
        }
    }
}

void termWrite(terminal_t* term, char* str) {
    ASSERT(term != NULL);
    ASSERT(str != NULL);

    while (*str) {
        termFeed(term, *str++);
    }
}

void termFlush(terminal_t* term) {
    term->cursorCounter++;

    if (term->cursorCounter >= 30) {
        term->cursorVisible = !term->cursorVisible;
        term->cursorCounter = 0;
    }

    termRenderer(term);    
}
