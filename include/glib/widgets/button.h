#pragma once

#include <glib/containers/widget.h>
#include <glib/fonts/font.h>

typedef struct button {
    widget_t widget;

    font_t* font;
    char* text;
    uint32_t textColor;

    uint32_t bgColor;
    uint32_t hoverColor;
    uint32_t pressedColor;

    bool hovered;
    bool pressed;

    void (*onClick)(struct button*, void*);
    void* userData;
} button_t;

void buttonInit(button_t* button, int x, int y, int w, int h, font_t* font, char* text);
