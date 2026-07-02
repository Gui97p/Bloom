#include <glib/gfx/context.h>
#include <glib/gfx/rect.h>
#include <glib/gfx/line.h>
#include <glib/gfx/blit.h>
#include <services/desktop/desktop.h>

#include <bloom/theme.h>

void desktopDrawTaskbar(taskbar_t* taskbar) {
    gfxFillRect(&taskbar->surface, 0, 0, taskbar->surface.width, taskbar->surface.height, taskbar->bg);
    gfxDrawHLine(&taskbar->surface, 0, taskbar->surface.width, 0, bloomTheme.ui.pallete.border);
}

static void taskbarInit(taskbar_t* taskbar, int width, int height) {
    widgetContainerInit(&taskbar->container, &bloomTheme.ui);
    gfxCreateSurface(&taskbar->surface, width, height);
    taskbar->bg = bloomTheme.ui.pallete.surface;
}

void desktopInit(desktop_t* desktop, gfxContext_t* ctx) {
    desktop->surface = ctx->backbuffer;
    desktop->bg = bloomTheme.desktopBackground;
    taskbarInit(&desktop->taskbar, ctx->width, 50);
    widgetContainerInit(&desktop->container, &bloomTheme.ui);
}
