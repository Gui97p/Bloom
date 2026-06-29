#pragma once

#include <glib/widgets/widget.h>
#include <glib/fonts/font.h>

typedef struct {
    widget_t widget;

    font_t* font;

    char* buffer;
    size_t capacity;
    size_t length;
    size_t cursor;

    size_t selectionStart;
    size_t selectionEnd;

    uint32_t fg;
    uint32_t bg;

    bool cursorVisible;
    bool selecting;
    size_t scrollX;

    bool readOnly;
} textBox_t;

void textBoxInit(textBox_t* textBox, int x, int y, int w, int h, char* buffer, size_t capacity);
