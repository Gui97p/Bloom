#include <stdlib.h>
#include <string.h>

#include <glib/containers/window.h>
#include <glib/containers/widget.h>

static void windowDispatchEvent(gfxWindow_t* win, event_t* ev) {
    widgetContainerDispatchEvent(&win->container, ev);
}

void gfxCreateWindow(gfxWindow_t* win, int width, int height, char* title) {
    gfxCreateSurface(&win->surface, width, height);
    widgetContainerInit(&win->container);
    
    win->x = 0;
    win->y = 0;
    win->zIndex = 0;
    
    win->visible = true;
    win->focused = false;
    
    win->onDraw = NULL;
    win->onEvent = windowDispatchEvent;
    win->onWindowEvent = NULL;
    
    strcpy(win->title, title);
    win->titleBarHeight = TITLE_BAR_HEIGHT;
    
    win->drawBackground = true;
    win->backgroundColor = 0x222222;
    
    win->next = NULL;
}

void windowAddWidget(gfxWindow_t* win, widget_t* widget) {
    widget->next = NULL;

    if (!win->container.widgets) {
        win->container.widgets = widget;
    } else if (widget->zIndex < win->container.widgets->zIndex) {
        widget->next = win->container.widgets;
        win->container.widgets = widget;
    } else {
        for (widget_t* w = win->container.widgets; w; w = w->next) {
            if (!w->next || widget->zIndex <= w->next->zIndex) {
                widget->next = w->next;
                w->next = widget;
                break;
            }
        }
    }

    widget->container = &win->container;
}

void drawWidgets(gfxWindow_t* win) {
    for (widget_t* w = win->container.widgets; w; w = w->next) {
        if (w->visible && w->draw) w->draw(w, &win->surface);
    }
}
