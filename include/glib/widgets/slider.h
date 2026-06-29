#pragma once

#include <glib/widgets/widget.h>
#include <stdbool.h>

typedef struct slider {
    widget_t widget;

    int value;
    int max;

    bool dragging;

    void (*onChanged)(struct slider*, int value, void* userdata);

    uint32_t fg;
    uint32_t bg;
    uint32_t borderColor;
} slider_t;

void sliderInit(slider_t* progressBar, int x, int y, int w, int h, int max);
