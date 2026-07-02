#include <glib/gfx/rect.h>
#include <glib/gfx/frame.h>
#include <glib/theme/ui.h>

static void panelDraw(widget_t* widget, gfxSurface_t* surface) {
    panel_t* panel = (panel_t*)widget;

    panelStyle_t* style = &panel->style;

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, style->bg);
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);
}

static void panelApplyTheme(widget_t* widget) {
    panel_t* panel = (panel_t*)widget;
    panelStyle_t* theme = &widget->container->theme->panel;
    panel->style = *theme;

    WIDGET_APPLY_IF(panel, bg, PANEL_CUSTOM_BG, theme->bg);

    WIDGET_FRAME_APPLY_IF(panel, border, PANEL_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(panel, borderRadius, PANEL_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(panel, borderSize,  PANEL_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(panel, borderColor, PANEL_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void panelInit(panel_t* panel, widgetContainer_t* container, int x, int y, int w, int h, uint32_t color) {
    widgetInit(&panel->widget, x, y, w, h, WIDGET_PANEL);

    panel->widget.draw = panelDraw;
    panel->widget.applyTheme = panelApplyTheme;
    
    panel->customFields = PANEL_CUSTOM_NONE;

    widgetContainerAddWidget(container, &panel->widget);
}
