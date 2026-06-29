#pragma once

#include <glib/widgets/widget.h>
#include <glib/fonts/font.h>

typedef struct checkBox {
    widget_t widget;

    bool checked;

    font_t* font;
    char* text;

    uint32_t borderColor;
    uint32_t fg;
    uint32_t rectColor;

    void (*onChanged)(struct checkBox*, bool checked, void* userdata);
} checkBox_t;

void checkBoxInit(checkBox_t* checkBox, int x, int y, int w, int h, font_t* font, char* text);
