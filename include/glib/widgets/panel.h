#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>

typedef enum {
    PANEL_CUSTOM_NONE          = 0,

    PANEL_CUSTOM_BG            = 1 << 0,

    PANEL_CUSTOM_BORDER        = 1 << 1,
    PANEL_CUSTOM_BORDER_RADIUS = 1 << 2,
    PANEL_CUSTOM_BORDER_SIZE   = 1 << 3,
    PANEL_CUSTOM_BORDER_COLOR  = 1 << 4,
} panelCustomField_t;

typedef struct {
    frameStyle_t frame;

    uint32_t bg;
} panelStyle_t;

typedef struct {
    widget_t widget;

    panelStyle_t style;
    uint32_t customFields;
} panel_t;

void panelInit(panel_t* panel, widgetContainer_t* container, int x, int y, int w, int h, uint32_t color);
