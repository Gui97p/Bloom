#pragma once

#include <glib/widgets/widget.h>
#include <glib/fonts/font.h>

typedef struct {
    widget_t widget;

    uint32_t color;
} panel_t;

void panelInit(panel_t* panel, int x, int y, int w, int h, uint32_t color);
