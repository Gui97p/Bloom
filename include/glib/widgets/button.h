#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>
#include <glib/fonts/font.h>

typedef enum {
    BUTTON_CUSTOM_NONE          = 0,
    
    BUTTON_CUSTOM_BG            = 1 << 0,
    BUTTON_CUSTOM_BG_HOVER      = 1 << 1,
    BUTTON_CUSTOM_BG_PRESS      = 1 << 2,

    BUTTON_CUSTOM_FG            = 1 << 3,
    
    BUTTON_CUSTOM_BORDER        = 1 << 4,
    BUTTON_CUSTOM_BORDER_RADIUS = 1 << 5,
    BUTTON_CUSTOM_BORDER_SIZE   = 1 << 6,
    BUTTON_CUSTOM_BORDER_COLOR  = 1 << 7,
} buttonCustomField_t;

typedef struct {
    frameStyle_t frame;

    uint32_t fg;
    
    uint32_t bg;
    uint32_t bgHover;
    uint32_t bgPress;
} buttonStyle_t;

typedef struct button {
    widget_t widget;

    font_t* font;
    char* text;

    bool hovered;
    bool pressed;

    void (*onClick)(struct button*, void*);
    void* userData;

    buttonStyle_t style;
    uint32_t customFields;
} button_t;

void buttonInit(button_t* button, widgetContainer_t* container, int x, int y, int w, int h, char* text);
