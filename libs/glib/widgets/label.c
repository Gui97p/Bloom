#include <glib/gfx/rect.h>
#include <glib/gfx/frame.h>
#include <glib/theme/ui.h>
#include <glib/containers/widget.h>

static void labelDraw(widget_t* widget, gfxSurface_t* surface) {
    label_t* label = (label_t*)widget;

    labelStyle_t* style = &label->style;
    font_t* font = label->font;

    if (!font)
        font = widget->container->theme->defaultFont;
    
    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, style->bg);
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);
    gfxDrawString(surface, font, widget->x, widget->y, label->text, style->fg);
}

static void labelApplyTheme(widget_t* widget) {
    label_t* label = (label_t*)widget;
    labelStyle_t* theme = &widget->container->theme->label;
    label->style = *theme;

    WIDGET_APPLY_IF(label, fg, LABEL_CUSTOM_FG, theme->fg);
    WIDGET_APPLY_IF(label, bg, LABEL_CUSTOM_BG, theme->bg);
    
    WIDGET_FRAME_APPLY_IF(label, border, LABEL_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(label, borderRadius, LABEL_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(label, borderSize,  LABEL_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(label, borderColor, LABEL_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void labelInit(label_t* label, widgetContainer_t* container, int x, int y, int w, int h, char* text) {
    widgetInit(&label->widget, x, y, w, h, WIDGET_LABEL);

    label->widget.draw = labelDraw;
    label->widget.applyTheme = labelApplyTheme;
    
    label->customFields = LABEL_CUSTOM_NONE;
    
    label->font = NULL;
    label->text = text;
    
    widgetContainerAddWidget(container, &label->widget);
}
