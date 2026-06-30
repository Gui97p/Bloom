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
    WIDGET_TEXTBOX,
    WIDGET_CHECKBOX,
    WIDGET_PROGRESSBAR,
    WIDGET_SLIDER
} widgetType_t;

typedef struct widgetContainer widgetContainer_t;

typedef struct widget {
    int x, y;
    int width;
    int height;
    int zIndex;

    bool visible;
    bool focused;
    bool captureMouse;

    widgetType_t type;
    void* userData;

    void (*draw)(struct widget* widget, gfxSurface_t* surface);
    void (*onWidgetEvent)(struct widget* widget, widgetEvent_t* ev);
    void (*onEvent)(struct widget* widget, event_t* ev);

    struct widget* next;
    widgetContainer_t* container;
} widget_t;

struct widgetContainer {
    widget_t* widgets;
    widget_t* focusedWidget;
    widget_t* hoveredWidget;
    widget_t* capturedWidget;
};

widget_t* widgetHitTest(widgetContainer_t* container, int x, int y);
void widgetInit(widget_t* widget, int x, int y, int w, int h, widgetType_t type);
void widgetContainerDispatchEvent(widgetContainer_t* container, event_t* ev);
void widgetContainerCaptureMouse(widgetContainer_t* container, widget_t* widget);
void widgetContainerReleaseMouse(widgetContainer_t* container);
void widgetContainerInit(widgetContainer_t* container);