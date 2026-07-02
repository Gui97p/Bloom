#pragma once

#include <glib/gfx/frame.h>
#include <glib/containers/widget.h>
#include <stdbool.h>

typedef enum {
    SLIDER_CUSTOM_NONE          = 0,

    SLIDER_CUSTOM_BG            = 1 << 0,
    SLIDER_CUSTOM_FG            = 1 << 1,
    SLIDER_CUSTOM_KNOB          = 1 << 2,

    SLIDER_CUSTOM_BORDER        = 1 << 3,
    SLIDER_CUSTOM_BORDER_RADIUS = 1 << 4,
    SLIDER_CUSTOM_BORDER_SIZE   = 1 << 5,
    SLIDER_CUSTOM_BORDER_COLOR  = 1 << 6,
} sliderCustomField_t;

typedef struct {
    frameStyle_t frame;

    uint32_t fg;
    uint32_t bg;
    uint32_t knob;
} sliderStyle_t;

typedef struct slider {
    widget_t widget;

    int value;
    int max;

    bool dragging;

    void (*onChanged)(struct slider*, int value, void* userData);
    void* userData;

    sliderStyle_t style;
    uint32_t customFields;
} slider_t;

void sliderInit(slider_t* slider, widgetContainer_t* container, int x, int y, int w, int h, int max);