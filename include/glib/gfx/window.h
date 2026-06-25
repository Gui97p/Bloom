#pragma once

#include <glib/gfx/context.h>
#include <glib/input/event.h>

#define MAX_WINDOWS 64

typedef enum {
    WINDOW_EVENT_FOCUS,
    WINDOW_EVENT_UNFOCUS,
    WINDOW_EVENT_RESIZE,
    WINDOW_EVENT_CLOSE
} windowEventType_t;

typedef struct {
    windowEventType_t type;

    union {
        struct {
            int width;
            int height;
        } resize;
    };
} windowEvent_t;

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
    void (*onWindowEvent)(struct gfxWindow* win, windowEvent_t* ev);
    void* userData;

    struct gfxWindow* next;
} gfxWindow_t;
