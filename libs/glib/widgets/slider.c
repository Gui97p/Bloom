#include <glib/gfx/rect.h>
#include <glib/gfx/circle.h>
#include <glib/containers/widget.h>
#include <glib/theme/ui.h>
#include <glib/input/event.h>

#include <bloom/debug.h>

static void sliderDraw(widget_t* widget, gfxSurface_t* surface) {
    slider_t* slider = (slider_t*)widget;

    sliderStyle_t* style = &slider->style;
    
    if (slider->value < 0) slider->value = 0;
    if (slider->value > slider->max) slider->value = slider->max;

    int cx = (slider->value * widget->width) / slider->max;
    
    gfxFillRect(surface, widget->x, widget->y, cx, widget->height, style->bg);
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);
    gfxFillRect(surface, widget->x + cx, widget->y, widget->width - cx, widget->height, style->fg);
    gfxFillCircle(surface, widget->x + cx, widget->y + (widget->height)/2, (widget->height * 2)/3, style->knob);
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
            int pos = slider->value;

            if (pos < 0)
                pos = 0;
            if (pos > slider->max)
                pos = slider->max;

            int cx = (pos * widget->width) / slider->max;

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

static void sliderApplyTheme(widget_t* widget) {
    slider_t* slider = (slider_t*)widget;
    sliderStyle_t* theme = &widget->container->theme->slider;
    slider->style = *theme;

    WIDGET_APPLY_IF(slider, fg, SLIDER_CUSTOM_FG, theme->fg);
    WIDGET_APPLY_IF(slider, bg, SLIDER_CUSTOM_BG, theme->bg);
    WIDGET_APPLY_IF(slider, knob, SLIDER_CUSTOM_KNOB, theme->knob);

    WIDGET_FRAME_APPLY_IF(slider, border, SLIDER_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(slider, borderRadius, SLIDER_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(slider, borderSize,  SLIDER_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(slider, borderColor, SLIDER_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void sliderInit(slider_t* slider, widgetContainer_t* container, int x, int y, int w, int h, int max) {
    ASSERT(max != 0);
    widgetInit(&slider->widget, x, y, w, h, WIDGET_SLIDER);

    slider->widget.draw = sliderDraw;
    slider->widget.onEvent = sliderEvent;
    slider->widget.onWidgetEvent = sliderWidgetEvent;
    slider->widget.applyTheme = sliderApplyTheme;
    
    slider->customFields = SLIDER_CUSTOM_NONE;

    slider->onChanged = NULL;
    
    slider->value = 0;
    slider->max = max;
    
    slider->dragging = false;

    widgetContainerAddWidget(container, &slider->widget);
}
