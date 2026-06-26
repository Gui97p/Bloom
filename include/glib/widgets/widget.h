#pragma once

#include <stdbool.h>

#include <glib/gfx/context.h>
#include <glib/input/event.h>

struct gfxWindow;
typedef struct gfxWindow gfxWindow_t;

#define MAX_WIDGETS 64

typedef enum {
    WIDGET_EVENT_FOCUS,
    WIDGET_EVENT_UNFOCUS,

    WIDGET_EVENT_MOUSE_LEAVE,
    WIDGET_EVENT_MOUSE_ENTER,

    WIDGET_EVENT_RESIZE,
    WIDGET_EVENT_DESTROY
} widgetEventType_t;

typedef struct {
    widgetEventType_t type;
} widgetEvent_t;

typedef enum {
    WIDGET_LABEL,
    WIDGET_BUTTON,
    WIDGET_PANEL,
    WIDGET_TEXTBOX
} widgetType_t;

typedef struct widget {
    int x, y;
    int width;
    int height;
    int zIndex;

    bool visible;
    bool focused;

    widgetType_t type;
    void* userData;

    void (*draw)(struct widget* widget, gfxSurface_t* surface);
    void (*onWidgetEvent)(struct widget* widget, widgetEvent_t* ev);
    void (*onEvent)(struct widget* widget, event_t* ev);

    struct widget* next;
} widget_t;

widget_t* widgetHitTest(gfxWindow_t* win, int x, int y);
void widgetInit(widget_t* widget, int x, int y, int w, int h, widgetType_t type);