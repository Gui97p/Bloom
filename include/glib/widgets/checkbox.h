#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>
#include <glib/fonts/font.h>

typedef enum {
    CHECKBOX_CUSTOM_NONE            = 0,

    CHECKBOX_CUSTOM_BG              = 1 << 0,
    CHECKBOX_CUSTOM_BG_HOVER        = 1 << 1,
    CHECKBOX_CUSTOM_BG_ACTIVE       = 1 << 2,
    CHECKBOX_CUSTOM_BG_HOVER_ACTIVE = 1 << 3,

    CHECKBOX_CUSTOM_BORDER          = 1 << 4,
    CHECKBOX_CUSTOM_BORDER_RADIUS   = 1 << 5,
    CHECKBOX_CUSTOM_BORDER_SIZE     = 1 << 6,
    CHECKBOX_CUSTOM_BORDER_COLOR    = 1 << 7,
} checkBoxCustomField_t;

typedef struct {
    frameStyle_t frame;

    uint32_t bg;
    uint32_t bgHover;
    uint32_t bgActive;
    uint32_t bgHoverActive;
} checkBoxStyle_t;

typedef struct checkBox {
    widget_t widget;

    bool checked;
    bool hovered;

    void (*onChanged)(struct checkBox*, bool checked, void* userdata);
    
    checkBoxStyle_t style;
    uint32_t customFields;
} checkBox_t;

void checkBoxInit(checkBox_t* checkBox, widgetContainer_t* container, int x, int y, int w, int h);
