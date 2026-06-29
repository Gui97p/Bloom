#include <glib/gfx/window.h>
#include <glib/widgets/widget.h>

widget_t* widgetHitTest(gfxWindow_t* win, int x, int y) {
    widget_t* topHit = NULL;

    for (widget_t* w = win->widgets; w; w = w->next) {
        if (!w->visible) continue;
        
        if (x >= w->x && x < w->x + w->width &&
            y >= w->y && y < w->y + w->height) {
            topHit = w;
        }
    }

    return topHit;
}

void widgetInit(widget_t* widget, int x, int y, int w, int h, widgetType_t type) {
    widget->x = x;
    widget->y = y;

    widget->width = w;
    widget->height = h;

    widget->zIndex = 0;

    widget->visible = true;
    widget->focused = false;
    widget->captureMouse = false;

    widget->type = type;
    widget->userData = NULL;

    widget->draw = NULL;
    widget->onWidgetEvent = NULL;
    widget->onEvent = NULL;

    widget->next = NULL;
    widget->window = NULL;
}
