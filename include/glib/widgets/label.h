#pragma once

#include <glib/widgets/widget.h>
#include <glib/fonts/font.h>

typedef struct {
    widget_t widget;

    font_t* font;
    char* text;

    uint32_t fg;
    uint32_t bg;

    bool showBackground;
} label_t;

void labelInit(label_t* label, int x, int y, int w, int h, font_t* font, char* text);
