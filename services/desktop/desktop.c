#include <glib/gfx/context.h>
#include <glib/gfx/rect.h>
#include <glib/gfx/blit.h>
#include <services/desktop/desktop.h>

void desktopDrawBackground(desktop_t* desktop) {
    gfxFillRect(desktop->surface, 0, 0, desktop->surface->width, desktop->surface->height, desktop->bg);
    gfxBlit(desktop->surface, &desktop->taskbar.surface, 0, desktop->surface->height - desktop->taskbar.surface.height);
}

void desktopDrawTaskbar(taskbar_t* taskbar) {
    gfxFillRect(&taskbar->surface, 0, 0, taskbar->surface.width, taskbar->surface.height, taskbar->bg);
}

static void taskbarInit(taskbar_t* taskbar, int width, int height) {
    widgetContainerInit(&taskbar->container);
    gfxCreateSurface(&taskbar->surface, width, height);
    taskbar->bg = 0x999999;
}

void desktopInit(desktop_t* desktop, gfxContext_t* ctx) {
    widgetContainerInit(&desktop->container);
    taskbarInit(&desktop->taskbar, ctx->width, 50);
    
    desktop->surface = &ctx->backbuffer;
    desktop->bg = 0x0F0A1A;
}
