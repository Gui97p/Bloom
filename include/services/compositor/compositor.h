#pragma once

#include <glib/gfx/context.h>
#include <glib/containers/window.h>
#include <services/desktop/desktop.h>

#define RESIZE_MARGIN 6

typedef struct {
    gfxWindow_t* dragging;
    int dragOffsetX;
    int dragOffsetY;

    gfxWindow_t* focusedWindow;

    gfxWindow_t* resizingWindow;
    int resizeStartW, resizeStartH;
    int resizeStartMouseX, resizeStartMouseY;

    int mouseX, mouseY;
} compositorState_t;

void compositorLoop(gfxContext_t* ctx, desktop_t* desktop);
