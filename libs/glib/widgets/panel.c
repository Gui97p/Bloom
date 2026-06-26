#include <glib/gfx/rect.h>
#include <glib/widgets/panel.h>

static void panelDraw(widget_t* widget, gfxSurface_t* surface) {
    panel_t* panel = (panel_t*)widget;

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, panel->color);
}


void panelInit(panel_t* panel, int x, int y, int w, int h, uint32_t color) {
    widgetInit(&panel->widget, x, y, w, h, WIDGET_PANEL);

    panel->widget.draw = panelDraw;

    panel->color = color;
}
