#include <bin/terminal/terminal.h>
#include <glib/gfx/rect.h>

void termDrawCursor(terminal_t* term) {
    int x = term->cursorX * term->font->width;
    int y = term->cursorY * term->font->height;
    
    gfxFillRect(&term->viewport, x, y, term->font->width / 8, term->font->height, term->theme->accent_bright);
}

void termSetCursor(terminal_t* term, int x, int y) {
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    if (x >= term->cols)
        x = term->cols - 1;
    if (y >= term->rows)
        y = term->rows - 1;

    term->cursorX = x;
    term->cursorY = y;
}

void termMoveCursor(terminal_t* term, int dx, int dy) {
    termSetCursor(
        term,
        term->cursorX + dx,
        term->cursorY + dy
    );
}

void termMoveCursorLeft(terminal_t* term) {
    if (term->cursorX > 0)
        term->cursorX--;
}

void termMoveCursorRight(terminal_t* term) {
    if (term->cursorX < term->cols - 1)
        term->cursorX++;
}

void termMoveCursorUp(terminal_t* term) {
    if (term->cursorY > 0)
        term->cursorY--;
}

void termMoveCursorDown(terminal_t* term) {
    if (term->cursorY < term->rows - 1)
        term->cursorY++;
}

int termGetCursorX(terminal_t* term) {
    return term->cursorX;
}

int termGetCursorY(terminal_t* term) {
    return term->cursorY;
}