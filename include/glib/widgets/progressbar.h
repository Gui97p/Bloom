#pragma once

#include <glib/containers/widget.h>

typedef struct {
    widget_t widget;

    int value;
    int max;

    uint32_t fg;
    uint32_t bg;
    uint32_t borderColor;
} progressBar_t;

void progressBarInit(progressBar_t* progressBar, int x, int y, int w, int h, int max);
