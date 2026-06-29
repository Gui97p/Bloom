#include <glib/gfx/rect.h>
#include <glib/widgets/progressbar.h>
#include <bloom/debug.h>

static void progressBarDraw(widget_t* widget, gfxSurface_t* surface) {
    progressBar_t* progressBar = (progressBar_t*)widget;

    if (progressBar->value < 0) progressBar->value = 0;
    if (progressBar->value > progressBar->max) progressBar->value = progressBar->max;

    double delta = ((double)progressBar->value / (double)progressBar->max);

    gfxFillRect(surface, widget->x, widget->y, (int)(widget->width * delta), widget->height, progressBar->fg);
    gfxFillRect(surface, widget->x + ((int)(widget->width * delta)), widget->y, (int)(widget->width * (1 - delta)), widget->height, progressBar->bg);
    gfxDrawRect(surface, widget->x, widget->y, widget->width, widget->height, progressBar->borderColor);
}

void progressBarInit(progressBar_t* progressBar, int x, int y, int w, int h, int max) {
    ASSERT(max != 0);

    widgetInit(&progressBar->widget, x, y, w, h, WIDGET_PROGRESSBAR);

    progressBar->widget.draw = progressBarDraw;
    
    progressBar->borderColor = 0x000000;
    progressBar->bg = 0xCCCCCC;
    progressBar->fg = 0x3333AA;

    progressBar->value = 0;
    progressBar->max = max;
}
