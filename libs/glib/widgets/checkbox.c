#include <glib/gfx/rect.h>
#include <glib/widgets/checkbox.h>

static void checkBoxDraw(widget_t* widget, gfxSurface_t* surface) {
    checkBox_t* checkBox = (checkBox_t*)widget;

    if (checkBox->checked) {
        gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, checkBox->rectColor);
    }
    gfxDrawRect(surface, widget->x, widget->y, widget->width, widget->height, checkBox->borderColor);

    gfxDrawString(surface, checkBox->font, widget->x + widget->width + 6, widget->y + 6, checkBox->text, checkBox->fg);
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

void checkBoxInit(checkBox_t* checkBox, int x, int y, int w, int h, font_t* font, char* text) {
    widgetInit(&checkBox->widget, x, y, w, h, WIDGET_CHECKBOX);

    checkBox->widget.draw = checkBoxDraw;
    checkBox->widget.onEvent = checkBoxEvent;

    checkBox->font = font;
    checkBox->text = text;

    checkBox->fg = 0xFFFFFF;
    checkBox->borderColor = 0x000000;
    checkBox->rectColor = 0x88E788;

    checkBox->checked = false;
    checkBox->onChanged = NULL;
}
