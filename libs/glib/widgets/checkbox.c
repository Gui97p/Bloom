#include <glib/gfx/rect.h>
#include <glib/theme/ui.h>

static void checkBoxDraw(widget_t* widget, gfxSurface_t* surface) {
    checkBox_t* checkBox = (checkBox_t*)widget;

    checkBoxStyle_t* style = &checkBox->style;

    uint32_t bgColor = checkBox->hovered ? 
        (checkBox->checked ? style->bgHoverActive : style->bgHover) : 
        (checkBox->checked ? style->bgActive : style->bg);
    
    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, bgColor);
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);
}

static void checkBoxEvent(widget_t* widget, event_t* ev) {
    checkBox_t* checkBox = (checkBox_t*)widget;

    switch (ev->type) {
        case EVENT_MOUSE_DOWN: {
            checkBox->checked = !checkBox->checked;
            if (checkBox->onChanged)
                checkBox->onChanged(checkBox, checkBox->checked, widget->userData);
            
            break;
        }

        default:
            break;
    }
}

static void checkBoxWidgetEvent(widget_t* widget, widgetEvent_t* ev) {
    checkBox_t* checkBox = (checkBox_t*)widget;
    
    switch (ev->type)
    {
    case WIDGET_EVENT_MOUSE_ENTER: {
        checkBox->hovered = true;
        break;
    }
    
    case WIDGET_EVENT_MOUSE_LEAVE: {
        checkBox->hovered = false;
        break;
    }

    case WIDGET_EVENT_UNFOCUS: {
        checkBox->hovered = false;
        break;
    }
    
    default:
        break;
    }
}

static void checkBoxApplyTheme(widget_t* widget) {
    checkBox_t* checkBox = (checkBox_t*)widget;
    checkBoxStyle_t* theme = &widget->container->theme->checkBox;
    checkBox->style = *theme;

    WIDGET_APPLY_IF(checkBox, bg, CHECKBOX_CUSTOM_BG, theme->bg);
    WIDGET_APPLY_IF(checkBox, bgHover, CHECKBOX_CUSTOM_BG_HOVER, theme->bgHover);
    WIDGET_APPLY_IF(checkBox, bgActive, CHECKBOX_CUSTOM_BG_ACTIVE, theme->bgActive);
    WIDGET_APPLY_IF(checkBox, bgHoverActive, CHECKBOX_CUSTOM_BG_HOVER_ACTIVE, theme->bgHoverActive);

    WIDGET_FRAME_APPLY_IF(checkBox, border, CHECKBOX_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(checkBox, borderRadius, CHECKBOX_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(checkBox, borderSize,  CHECKBOX_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(checkBox, borderColor, CHECKBOX_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void checkBoxInit(checkBox_t* checkBox, widgetContainer_t* container, int x, int y, int w, int h) {
    widgetInit(&checkBox->widget, x, y, w, h, WIDGET_CHECKBOX);
    
    checkBox->widget.draw = checkBoxDraw;
    checkBox->widget.onEvent = checkBoxEvent;
    checkBox->widget.onWidgetEvent = checkBoxWidgetEvent;
    checkBox->widget.applyTheme = checkBoxApplyTheme;

    checkBox->customFields = CHECKBOX_CUSTOM_NONE;
    
    checkBox->checked = false;
    checkBox->onChanged = NULL;

    widgetContainerAddWidget(container, &checkBox->widget);
}
