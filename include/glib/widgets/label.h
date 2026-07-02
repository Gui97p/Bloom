#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>
#include <glib/fonts/font.h>

typedef enum {
    LABEL_CUSTOM_NONE            = 0,

    LABEL_CUSTOM_BG              = 1 << 0,
    LABEL_CUSTOM_FG              = 1 << 1,

    LABEL_CUSTOM_BORDER          = 1 << 2,
    LABEL_CUSTOM_BORDER_RADIUS   = 1 << 3,
    LABEL_CUSTOM_BORDER_SIZE     = 1 << 4,
    LABEL_CUSTOM_BORDER_COLOR    = 1 << 5,
} labelCustomField_t;

typedef struct {
    frameStyle_t frame;

    uint32_t fg;
    uint32_t bg;
} labelStyle_t;

typedef struct {
    widget_t widget;

    font_t* font;
    char* text;

    labelStyle_t style;
    uint32_t customFields;
} label_t;

void labelInit(label_t* label, widgetContainer_t* container, int x, int y, int w, int h, char* text);
