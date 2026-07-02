#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>
#include <glib/fonts/font.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TEXTBOX_CUSTOM_NONE             = 0,

    TEXTBOX_CUSTOM_BG               = 1 << 0,
    TEXTBOX_CUSTOM_FG               = 1 << 1,
    TEXTBOX_CUSTOM_SELECTION_BG     = 1 << 2,
    TEXTBOX_CUSTOM_CURSOR_COLOR     = 1 << 3,

    TEXTBOX_CUSTOM_BORDER           = 1 << 4,
    TEXTBOX_CUSTOM_BORDER_RADIUS    = 1 << 5,
    TEXTBOX_CUSTOM_BORDER_SIZE      = 1 << 6,
    TEXTBOX_CUSTOM_BORDER_COLOR     = 1 << 7,
} textBoxCustomField_t;

typedef struct {
    frameStyle_t frame;

    uint32_t fg;
    uint32_t bg;
    uint32_t selectionBg;
    uint32_t cursorColor;
} textBoxStyle_t;

typedef struct {
    widget_t widget;

    font_t* font;

    char* buffer;
    size_t capacity;
    size_t length;
    size_t cursor;

    size_t selectionStart;
    size_t selectionEnd;

    bool cursorVisible;
    bool selecting;
    bool readOnly;
    size_t scrollX;

    textBoxStyle_t style;
    uint32_t customFields;
} textBox_t;

void textBoxInit(textBox_t* textBox, widgetContainer_t* container, int x, int y, int w, int h, char* buffer, size_t capacity);