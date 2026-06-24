#pragma once

#include <glib/gfx/context.h>
#include <glib/input/event.h>

typedef struct gfxWindow {
    gfxSurface_t surface;
    int x, y;
    int zIndex;
    int visible;
    int focused;

    char title[64];
    int titleBarHeight;

    void (*onDraw)(struct gfxWindow* win);
    void (*onMouseEvent)(struct gfxWindow* win, mouseEvent_t* ev);
    void (*onKeyEvent)(struct gfxWindow* win, keyEvent_t* ev);
    void* userData;

    struct gfxWindow* next;
} gfxWindow_t;
