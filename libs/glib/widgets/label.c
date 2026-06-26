#include <glib/widgets/label.h>
#include <glib/gfx/rect.h>

static void labelDraw(widget_t* widget, gfxSurface_t* surface) {
    label_t* label = (label_t*)widget;

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, label->bg);
    gfxDrawString(surface, label->font, widget->x, widget->y, label->text, label->fg);
}

void labelInit(label_t* label, int x, int y, int w, int h, font_t* font, char* text) {
    widgetInit(&label->widget, x, y, w, h, WIDGET_LABEL);

    label->widget.draw = labelDraw;

    label->font = font;
    label->text = text;
    label->fg = 0xFFFFFF;
    label->bg = 0x444444;
}
