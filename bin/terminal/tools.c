#include <string.h>
#include <bin/terminal/terminal.h>
#include <glib/gfx/rect.h>
#include <bloom/debug.h>

void termScroll(terminal_t* term) {
    DPRINTF("[TERMINAL] Scrolling 1 line down\n");

    for (int y = 1; y < term->rows; y++) {
        memcpy(
            &term->screen[(y - 1) * term->cols],
            &term->screen[y * term->cols],
            sizeof(termCell_t) * term->cols
        );
    }

    for (int x = 0; x < term->cols; x++) {
        termCell_t* cell = &CELL(term, term->rows - 1, x);
        cell->ch = '\0';
        cell->fg = term->currentFg;
        cell->bg = term->currentBg;
    }

    term->cursorY = term->rows - 1;
    memset(term->previous, 0xFF, term->rows * term->cols * sizeof(termCell_t));
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
