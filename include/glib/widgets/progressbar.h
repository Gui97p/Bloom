#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>

typedef enum {
    PROGRESSBAR_CUSTOM_NONE          = 0,

    PROGRESSBAR_CUSTOM_BG            = 1 << 0,
    PROGRESSBAR_CUSTOM_FG            = 1 << 1,

    PROGRESSBAR_CUSTOM_BORDER        = 1 << 2,
    PROGRESSBAR_CUSTOM_BORDER_RADIUS = 1 << 3,
    PROGRESSBAR_CUSTOM_BORDER_SIZE   = 1 << 4,
    PROGRESSBAR_CUSTOM_BORDER_COLOR  = 1 << 5,
} progressBarCustomField_t;

typedef struct {
    frameStyle_t frame;
    
    uint32_t fg;
    uint32_t bg;
} progressBarStyle_t;

typedef struct {
    widget_t widget;

    int value;
    int max;

    progressBarStyle_t style;
    uint32_t customFields;
} progressBar_t;

void progressBarInit(progressBar_t* progressBar, widgetContainer_t* container, int x, int y, int w, int h, int max);
