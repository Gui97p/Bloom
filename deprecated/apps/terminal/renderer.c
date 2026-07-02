#include <stdbool.h>
#include <apps/terminal/terminal.h>
#include <glib/gfx/rect.h>
#include <glib/gfx/blit.h>
#include <bloom/debug.h>

#include "tools.h"

static inline bool termCellEqual(termCell_t a, termCell_t b) {
    return a.ch == b.ch &&
           a.fg == b.fg &&
           a.bg == b.bg;
}

void termRenderer(terminal_t* term) {
    for (int row = 0; row < term->rows; row++) {
        for (int col = 0; col < term->cols; col++) {
            ASSERT(row < term->rows);
            ASSERT(col < term->cols);

            termCell_t cell = CELL(term, row, col);

            if (termCellEqual(cell, PCELL(term, row, col))) continue;

            int x = col * term->font->width;
            int y = row * term->font->height;

            gfxFillRect(
                &term->viewport,
                x,
                y,
                term->font->width,
                term->font->height,
                cell.bg
            );

            if (cell.ch != '\0') {
                gfxDrawChar(
                    &term->viewport,
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

    PCELL(term, term->cursorY, term->cursorX).ch = 0xFF;

    if (term->cursorVisible)
        termDrawCursor(term);
    
    if (term->viewport.hasDirty) {
        gfxBlit(term->surface, &term->viewport, 0, 0);
    }
    
}
