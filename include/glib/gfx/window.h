#pragma once

#include <glib/gfx/context.h>
#include <glib/input/event.h>
#include <glib/widgets/widget.h>

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

    widget_t* focusedWidget;
    widget_t* hoveredWidget;

    char title[64];
    int titleBarHeight;

    void (*onDraw)(struct gfxWindow* win);
    void (*onEvent)(struct gfxWindow* win, event_t* ev);
    void (*onWindowEvent)(struct gfxWindow* win, windowEvent_t* ev);

    uint32_t backgroundColor;
    bool drawBackground;

    widget_t* widgets;
    struct gfxWindow* next;
} gfxWindow_t;

void gfxCreateWindow(gfxWindow_t* win, int width, int height, char* title);
void windowAddWidget(gfxWindow_t* win, widget_t* widget);
void drawWidgets(gfxWindow_t* win);
