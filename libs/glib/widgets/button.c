#include <glib/gfx/rect.h>
#include <glib/widgets/button.h>

static void buttonDraw(widget_t* widget, gfxSurface_t* surface) {
    button_t* button = (button_t*)widget;

    uint32_t color = button->bgColor;

    if (button->pressed) {
        color = button->pressedColor;
    } else if (button->hovered) {
        color = button->hoverColor;
    }

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, color);
    gfxDrawRect(surface, widget->x, widget->y, widget->width, widget->height, 0x000000);

    gfxDrawString(surface, button->font, widget->x + 6, widget->y + 6, button->text, button->textColor);
}

static void buttonEvent(widget_t* widget, event_t* ev) {
    button_t* button = (button_t*)widget;

    switch (ev->type) {
        case EVENT_MOUSE_DOWN: {
            button->pressed = true;
            break;
        }

        case EVENT_MOUSE_UP: {
            if (button->pressed && button->onClick)
                button->onClick(button, button->widget.userData);

            button->pressed = false;
        }

        default:
            break;
    }
}

static void buttonWidgetEvent(widget_t* widget, widgetEvent_t* ev) {
    button_t* button = (button_t*)widget;

    switch (ev->type) {
        case WIDGET_EVENT_UNFOCUS: {
            button->pressed = false;
            button->hovered = false;
            break;
        }

        case WIDGET_EVENT_MOUSE_ENTER: {
            button->hovered = true;
            break;
        }

        case WIDGET_EVENT_MOUSE_LEAVE: {
            button->hovered = false;
            break;
        }

        default:
            break;
    }
}

void buttonInit(button_t* button, int x, int y, int w, int h, font_t* font, char* text) {
    widgetInit(&button->widget, x, y, w, h, WIDGET_BUTTON);

    button->widget.draw = buttonDraw;
    button->widget.onEvent = buttonEvent;
    button->widget.onWidgetEvent = buttonWidgetEvent;

    button->font = font;
    button->text = text;
    button->textColor = 0xFFFFFF;

    button->bgColor = 0x606060;
    button->hoverColor = 0x707070;
    button->pressedColor = 0x505050;

    button->hovered = false;
    button->pressed = false;

    button->onClick = NULL;
}
