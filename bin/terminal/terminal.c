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

static void termScroll(terminal_t* term) {
    for (int y = 1; y < term->rows; y++) {
        memcpy(
            &term->screen[(y - 1) * term->cols],
            &term->screen[y * term->cols],
            sizeof(termCell_t) * term->cols
        );
    }

    memset(
        &term->screen[(term->rows-1) * term->cols],
        0,
        sizeof(termCell_t) * term->cols
    );

    term->cursorY = term->rows - 1;

    memset(term->previous, 0xFF, term->rows * term->cols * sizeof(termCell_t));
}

void termInit(terminal_t* term, gfxContext_t* ctx, gfxSurface_t* surface) {
    term->gfx = ctx;
    term->viewport = surface;

    term->viewport->x = 16;
    term->viewport->y = 16;

    term->viewport->width = ctx->width - 32;
    term->viewport->height = ctx->height - 32;

    term->font = &font16x32;

    term->cols = term->viewport->width / term->font->width;
    term->rows = term->viewport->height / term->font->height;

    term->cursorX = 0;
    term->cursorY = 0;

    term->currentFg = 0xAAAAAA;
    term->currentBg = 0x1A001A;

    size_t size = term->rows * term->cols * sizeof(termCell_t);

    term->screen = malloc(size);
    term->previous = malloc(size);

    memset(term->screen, 0, size);
    memset(term->previous, 0, size);
    termClear(term);
    
    gfxBeginFrame(ctx);
    fillRect(ctx, 0, 0, ctx->width, ctx->height, term->currentBg);
    gfxEndFrame(ctx);
    
    memset(term->previous, 0xFF, size);
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
                CELL(term, term->cursorY, term->cursorX).ch = '\0';
            }
            break;
        }

        default: {
            if (term->cursorX < term->cols - 1) {
                termCell_t* cell = &CELL(term, term->cursorY, term->cursorX);

                cell->ch = c;
                cell->fg = fg;
                cell->bg = bg;

                term->cursorX++;

                if (term->cursorX < term->cols) {

                    CELL(term, term->cursorY, term->cursorX).ch = '\0';
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
            termCell_t cell = CELL(term, row, col);

            if (termCellEqual(cell, PCELL(term, row, col))) continue;

            int x = term->viewport->x + col * term->font->width;
            int y = term->viewport->y + row * term->font->height;

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
                    cell.fg
                );
            }

            PCELL(term, row, col) = cell;
                
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
            CELL(term, y, x).ch = '\0';
            CELL(term, y, x).fg = term->currentFg;
            CELL(term, y, x).bg = term->currentBg;
        }
    }

    memset(term->previous, 0xFF, term->rows * term->cols * sizeof(termCell_t));

    term->cursorX = 0;
    term->cursorY = 0;
}
