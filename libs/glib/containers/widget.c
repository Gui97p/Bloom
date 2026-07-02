#include <glib/containers/widget.h>

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

void widgetContainerDispatchEvent(widgetContainer_t* container, event_t* ev) {
    switch (ev->type) {
        case EVENT_MOUSE_DOWN: {
            widget_t* target = widgetHitTest(container, ev->mouse.x, ev->mouse.y);
        
            if (target != container->focusedWidget) {
                if (container->focusedWidget) {
                    container->focusedWidget->focused = false;
                    
                    sendWidgetEvent(container->focusedWidget, (widgetEvent_t){.type = WIDGET_EVENT_UNFOCUS});
                }
        
                container->focusedWidget = target;
                
                if (container->focusedWidget) {
                    container->focusedWidget->focused = true;
                
                    sendWidgetEvent(container->focusedWidget, (widgetEvent_t){.type = WIDGET_EVENT_FOCUS});
                }
            }

            if (target) {
                sendWidgetInputEvent(target, ev);
            }

            break;
        }

        case EVENT_KEY_DOWN:
        case EVENT_KEY_UP: {
            if (container->focusedWidget)
                sendWidgetInputEvent(container->focusedWidget, ev);
            break;
        }

        case EVENT_MOUSE_UP: {
            if (container->capturedWidget) {
                sendWidgetInputEvent(container->capturedWidget, ev);
                container->capturedWidget = NULL;
            } else {
                widget_t* target = widgetHitTest(container, ev->mouse.x, ev->mouse.y);
    
                if (target) {
                    sendWidgetInputEvent(target, ev);
                }
            }

            break;
        }

        case EVENT_MOUSE_MOVE: {
            if (container->capturedWidget) {
                sendWidgetInputEvent(container->capturedWidget, ev);
                container->capturedWidget = NULL;
            } else {
                widget_t* target = widgetHitTest(container, ev->mouse.x, ev->mouse.y);
    
                if (target != container->hoveredWidget) {
                    if (container->hoveredWidget) {
                        sendWidgetEvent(container->hoveredWidget, (widgetEvent_t){.type = WIDGET_EVENT_MOUSE_LEAVE});
                    }
    
                    container->hoveredWidget = target;
    
                    if (container->hoveredWidget) {
                        sendWidgetEvent(container->hoveredWidget, (widgetEvent_t){.type = WIDGET_EVENT_MOUSE_ENTER});
                    }
                }
    
                if (target) {
                    sendWidgetInputEvent(target, ev);
                }
            }

            break;
        }

        default:
            break;
    }
}

void widgetContainerAddWidget(widgetContainer_t* container, widget_t* widget) {
    widget->next = NULL;

    if (!container->widgets) {
        container->widgets = widget;
    } else if (widget->zIndex < container->widgets->zIndex) {
        widget->next = container->widgets;
        container->widgets = widget;
    } else {
        for (widget_t* w = container->widgets; w; w = w->next) {
            if (!w->next || widget->zIndex <= w->next->zIndex) {
                widget->next = w->next;
                w->next = widget;
                break;
            }
        }
    }

    widget->container = container;

    widgetApplyTheme(widget);
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
    widget->applyTheme = NULL;

    widget->container = NULL;
    widget->next = NULL;
}

widget_t* widgetHitTest(widgetContainer_t* container, int x, int y) {
    widget_t* topHit = NULL;

    for (widget_t* w = container->widgets; w; w = w->next) {
        if (!w->visible) continue;
        
        if (x >= w->x && x < w->x + w->width &&
            y >= w->y && y < w->y + w->height) {
            topHit = w;
        }
    }

    return topHit;
}

void widgetApplyTheme(widget_t* widget) {
    if (!widget->container)
        return;
    
    if (widget->applyTheme)
        widget->applyTheme(widget);
}

void widgetContainerInit(widgetContainer_t* container, uiTheme_t* theme) {
    container->widgets = NULL;
    container->capturedWidget = NULL;
    container->focusedWidget = NULL;
    container->hoveredWidget = NULL;
    container->theme = theme;
}

void widgetContainerSetTheme(widgetContainer_t* container, uiTheme_t* theme) {
    if (container->theme == theme)
        return;

    container->theme = theme;

    for (widget_t* w = container->widgets; w; w = w->next) {
        widgetApplyTheme(w);
    }
}

void widgetContainerCaptureMouse(widgetContainer_t* container, widget_t* widget) {
    container->capturedWidget = widget;
    widget->captureMouse = true;
}

void widgetContainerReleaseMouse(widgetContainer_t* container) {
    if (container->capturedWidget) {
        container->capturedWidget->captureMouse = false;
        container->capturedWidget = NULL;
    }
}
