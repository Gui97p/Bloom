#pragma once

#include <bin/terminal/terminal.h>

void drawCursor(terminal_t* term);
void termSetCursor(terminal_t* term, int x, int y);
void termMoveCursor(terminal_t* term, int dx, int dy);
void termMoveCursorLeft(terminal_t* term);
void termMoveCursorRight(terminal_t* term);
void termMoveCursorUp(terminal_t* term);
void termMoveCursorDown(terminal_t* term);
int termGetCursorX(terminal_t* term);
int termGetCursorY(terminal_t* term);
