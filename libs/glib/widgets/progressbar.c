#include <glib/gfx/rect.h>
#include <glib/theme/ui.h>
#include <bloom/debug.h>

static void progressBarDraw(widget_t* widget, gfxSurface_t* surface) {
    progressBar_t* progressBar = (progressBar_t*)widget;

    progressBarStyle_t* style = &progressBar->style;

    if (progressBar->value < 0) progressBar->value = 0;
    if (progressBar->value > progressBar->max) progressBar->value = progressBar->max;

    int limit = (progressBar->value * widget->width) / progressBar->max;

    gfxFillRect(surface, widget->x, widget->y, limit, widget->height, style->fg);
    gfxFillRect(surface, widget->x + limit, widget->y, widget->width - limit, widget->height, style->bg);
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);
}

static void progressBarApplyTheme(widget_t* widget) {
    progressBar_t* progressBar = (progressBar_t*)widget;
    progressBarStyle_t* theme = &widget->container->theme->progressBar;
    progressBar->style = *theme;

    WIDGET_APPLY_IF(progressBar, fg, PROGRESSBAR_CUSTOM_FG, theme->fg);
    WIDGET_APPLY_IF(progressBar, bg, PROGRESSBAR_CUSTOM_BG, theme->bg);

    WIDGET_FRAME_APPLY_IF(progressBar, border, PROGRESSBAR_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(progressBar, borderRadius, PROGRESSBAR_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(progressBar, borderSize,  PROGRESSBAR_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(progressBar, borderColor, PROGRESSBAR_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void progressBarInit(progressBar_t* progressBar, widgetContainer_t* container, int x, int y, int w, int h, int max) {
    ASSERT(max != 0);
    widgetInit(&progressBar->widget, x, y, w, h, WIDGET_PROGRESSBAR);

    progressBar->widget.draw = progressBarDraw;
    progressBar->widget.applyTheme = progressBarApplyTheme;
    
    progressBar->customFields = PROGRESSBAR_CUSTOM_NONE;
    
    progressBar->value = 0;
    progressBar->max = max;

    widgetContainerAddWidget(container, &progressBar->widget);
}
