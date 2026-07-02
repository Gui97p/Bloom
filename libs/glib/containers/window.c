#include <stdlib.h>
#include <string.h>

#include <glib/containers/window.h>
#include <glib/containers/widget.h>

#include <bloom/theme.h>

static void windowDispatchEvent(gfxWindow_t* win, event_t* ev) {
    widgetContainerDispatchEvent(&win->container, ev);
}

void gfxCreateWindow(gfxWindow_t* win, int width, int height, char* title) {
    gfxCreateSurface(&win->surface, width, height);
    widgetContainerInit(&win->container, &bloomTheme.ui);
    
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

    win->dirty = true;
}

void drawWidgets(gfxWindow_t* win) {
    for (widget_t* w = win->container.widgets; w; w = w->next) {
        if (w->visible && w->draw) w->draw(w, &win->surface);
    }
}

void gfxWindowInvalidate(gfxWindow_t* window) {
    window->dirty = true;
}
