#include <stdlib.h>
#include <string.h>

#include <glib/gfx/window.h>
#include <glib/widgets/widget.h>

static void sendWidgetEvent(widget_t* widget, widgetEvent_t ev) {
    if (widget && widget->onWidgetEvent) {
        widget->onWidgetEvent(widget, &ev);
    }
}

static void sendWidgetInputEvent(widget_t* widget, event_t* ev) {
    if (!widget || !widget->onEvent)
        return;
    
    event_t local = *ev;
    
    if (ev->type == EVENT_MOUSE_DOWN ||
        ev->type == EVENT_MOUSE_MOVE ||
        ev->type == EVENT_MOUSE_UP) {
        local.mouse.x -= widget->x;
        local.mouse.y -= widget->y;
    }

    widget->onEvent(widget, &local);
}

void windowDispatchEvent(gfxWindow_t* win, event_t* ev) {
    switch (ev->type) {
        case EVENT_MOUSE_DOWN: {
            widget_t* target = widgetHitTest(win, ev->mouse.x, ev->mouse.y);
        
            if (target != win->focusedWidget) {
                if (win->focusedWidget) {
                    win->focusedWidget->focused = false;
                    
                    sendWidgetEvent(win->focusedWidget, (widgetEvent_t){.type = WIDGET_EVENT_UNFOCUS});
                }
        
                win->focusedWidget = target;
                
                if (win->focusedWidget) {
                    win->focusedWidget->focused = true;
                
                    sendWidgetEvent(win->focusedWidget, (widgetEvent_t){.type = WIDGET_EVENT_FOCUS});
                }
            }

            if (target) {
                sendWidgetInputEvent(target, ev);
            }

            break;
        }

        case EVENT_KEY_DOWN:
        case EVENT_KEY_UP: {
            if (win->focusedWidget)
                sendWidgetInputEvent(win->focusedWidget, ev);
            break;
        }

        case EVENT_MOUSE_UP: {
            widget_t* target = widgetHitTest(win, ev->mouse.x, ev->mouse.y);

            if (target) {
                sendWidgetInputEvent(target, ev);
            }

            break;
        }
        case EVENT_MOUSE_MOVE: {
            widget_t* target = widgetHitTest(win, ev->mouse.x, ev->mouse.y);

            if (target != win->hoveredWidget) {
                if (win->hoveredWidget) {
                    sendWidgetEvent(win->hoveredWidget, (widgetEvent_t){.type = WIDGET_EVENT_MOUSE_LEAVE});
                }

                win->hoveredWidget = target;

                if (win->hoveredWidget) {
                    sendWidgetEvent(win->hoveredWidget, (widgetEvent_t){.type = WIDGET_EVENT_MOUSE_ENTER});
                }
            }

            if (target) {
                sendWidgetInputEvent(target, ev);
            }

            break;
        }

        default:
            break;
    }
}

void gfxCreateWindow(gfxWindow_t* win, int width, int height, char* title) {
    gfxCreateSurface(&win->surface, width, height);
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
    win->widgets = NULL;
    win->focusedWidget = NULL;
    win->hoveredWidget = NULL;
}

void windowAddWidget(gfxWindow_t* win, widget_t* widget) {
    widget->next = NULL;

    if (!win->widgets) {
        win->widgets = widget;
    } else if (widget->zIndex < win->widgets->zIndex) {
        widget->next = win->widgets;
        win->widgets = widget;
    } else {
        for (widget_t* w = win->widgets; w; w = w->next) {
            if (!w->next || widget->zIndex <= w->next->zIndex) {
                widget->next = w->next;
                w->next = widget;
                break;
            }
        }
    }
}

void drawWidgets(gfxWindow_t* win) {
    for (widget_t* w = win->widgets; w; w = w->next) {
        if (w->visible && w->draw) w->draw(w, &win->surface);
    }
}
