#include <string.h>

#include <glib/gfx/rect.h>
#include <glib/color/color.h>
#include <glib/theme/ui.h>

static uint32_t buttonColor(button_t* button) {
    if (button->pressed) {
        return button->style.bgPress;
    } else if (button->hovered) {
        return button->style.bgHover;
    } else {
        return button->style.bg;
    }
}

static void buttonDraw(widget_t* widget, gfxSurface_t* surface) {
    button_t* button = (button_t*)widget;

    buttonStyle_t* style = &button->style;
    font_t* font = button->font;

    if (!font)
        font = widget->container->theme->defaultFont;

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, buttonColor(button));
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);

    int tw = gfxMeasureString(font, strlen(button->text));
    int tx = widget->x + (widget->width - tw)/2;
    int ty = widget->y + (widget->height - font->height)/2;

    gfxDrawString(surface, font, tx, ty, button->text, style->fg);
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

            break;
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

static void buttonApplyTheme(widget_t* widget) {
    button_t* button = (button_t*)widget;
    buttonStyle_t* theme = &widget->container->theme->button;
    button->style = *theme;

    WIDGET_APPLY_IF(button, fg, BUTTON_CUSTOM_FG, theme->fg);
    WIDGET_APPLY_IF(button, bg, BUTTON_CUSTOM_BG, theme->bg);
    WIDGET_APPLY_IF(button, bgHover, BUTTON_CUSTOM_BG_HOVER, theme->bgHover);
    WIDGET_APPLY_IF(button, bgPress, BUTTON_CUSTOM_BG_PRESS, theme->bgPress);

    WIDGET_FRAME_APPLY_IF(button, border, BUTTON_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(button, borderRadius, BUTTON_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(button, borderSize,  BUTTON_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(button, borderColor, BUTTON_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void buttonInit(button_t* button, widgetContainer_t* container, int x, int y, int w, int h, char* text) {
    widgetInit(&button->widget, x, y, w, h, WIDGET_BUTTON);
    
    button->widget.draw = buttonDraw;
    button->widget.onEvent = buttonEvent;
    button->widget.onWidgetEvent = buttonWidgetEvent;
    button->widget.applyTheme = buttonApplyTheme;
    
    button->customFields = BUTTON_CUSTOM_NONE;

    button->font = NULL;
    button->text = text;
    
    button->hovered = false;
    button->pressed = false;
    
    button->onClick = NULL;
    
    widgetContainerAddWidget(container, &button->widget);
}
