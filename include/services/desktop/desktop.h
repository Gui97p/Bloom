#pragma once

#include <glib/gfx/context.h>
#include <glib/containers/widget.h>

typedef struct {
    gfxSurface_t surface;
    widgetContainer_t container;

    uint32_t bg;
} taskbar_t;

typedef struct {
    gfxSurface_t* surface;
    widgetContainer_t container;

    taskbar_t taskbar;

    uint32_t bg;
} desktop_t;

void desktopDrawBackground(desktop_t* desktop);
void desktopDrawTaskbar(taskbar_t* taskbar);
void desktopInit(desktop_t* desktop, gfxContext_t* ctx);
