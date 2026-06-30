#include <glib/gfx/rect.h>
#include <glib/gfx/circle.h>
#include <glib/containers/widget.h>
#include <glib/widgets/slider.h>
#include <glib/input/event.h>

#include <bloom/debug.h>

static void sliderDraw(widget_t* widget, gfxSurface_t* surface) {
    slider_t* slider = (slider_t*)widget;
    
    if (slider->value < 0) slider->value = 0;
    if (slider->value > slider->max) slider->value = slider->max;
    
    double delta = ((double)slider->value / (double)slider->max);
    
    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, slider->bg);
    gfxDrawRect(surface, widget->x, widget->y, widget->width, widget->height, slider->borderColor);
    gfxFillCircle(surface, widget->x + (widget->width * delta), widget->y + (widget->height)/2, (widget->height * 2)/3, slider->fg);
}

static void sliderWidgetEvent(widget_t* widget, widgetEvent_t* ev) {
    slider_t* slider = (slider_t*)widget;
    
    switch (ev->type) {
        case WIDGET_EVENT_UNFOCUS: {
            slider->dragging = false;
            widgetContainerReleaseMouse(widget->container);
            break;
        }

        default:
            break;
    }
}

static void sliderEvent(widget_t* widget, event_t* ev) {
    slider_t* slider = (slider_t*)widget;
    double delta = ((double)slider->value / (double)slider->max);
    
    switch (ev->type) {
        case EVENT_MOUSE_DOWN: {
            int r = (widget->height * 2)/3;
            int cx = widget->width * delta;

            if (ev->mouse.x >= cx - r && ev->mouse.x <= cx + r) {
                slider->dragging = true;
                widgetContainerCaptureMouse(widget->container, widget);
            }

            break;
        }

        case EVENT_MOUSE_UP: {
            slider->dragging = false;
            widgetContainerReleaseMouse(widget->container);
            break;
        }

        case EVENT_MOUSE_MOVE: {
            if (slider->dragging) {
                int pos = ev->mouse.x;

                if (pos < 0)
                    pos = 0;
                if (pos > widget->width)
                    pos = widget->width;

                int old = slider->value;
                slider->value = (pos * slider->max) / widget->width;

                if (slider->value != old && slider->onChanged)
                    slider->onChanged(slider, slider->value, widget->userData);
            }
            break;
        }

        default:
            break;
    }
}

void sliderInit(slider_t* slider, int x, int y, int w, int h, int max) {
    ASSERT(max != 0);

    widgetInit(&slider->widget, x, y, w, h, WIDGET_SLIDER);

    slider->widget.draw = sliderDraw;
    slider->widget.onEvent = sliderEvent;
    slider->widget.onWidgetEvent = sliderWidgetEvent;

    slider->onChanged = NULL;
    
    slider->borderColor = 0x000000;
    slider->bg = 0xCCCCCC;
    slider->fg = 0x3333AA;

    slider->value = 0;
    slider->max = max;

    slider->dragging = false;
}
