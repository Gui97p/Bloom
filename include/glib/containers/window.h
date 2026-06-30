#pragma once

#include <glib/gfx/context.h>
#include <glib/input/event.h>
#include <glib/containers/widget.h>

#define MAX_WINDOWS 64
#define TITLE_BAR_HEIGHT 24

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

    widgetContainer_t container;

    char title[64];
    int titleBarHeight;

    bool drawBackground;
    uint32_t backgroundColor;

    void (*onDraw)(struct gfxWindow* win);
    void (*onEvent)(struct gfxWindow* win, event_t* ev);
    void (*onWindowEvent)(struct gfxWindow* win, windowEvent_t* ev);

    struct gfxWindow* next;
} gfxWindow_t;

void gfxCreateWindow(gfxWindow_t* win, int width, int height, char* title);
void windowAddWidget(gfxWindow_t* win, widget_t* widget);
void drawWidgets(gfxWindow_t* win);
void windowCaptureMouse(gfxWindow_t* win, widget_t* widget);
void windowReleaseMouse(gfxWindow_t* win);
