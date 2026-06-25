#pragma once

#include <glib/gfx/context.h>
#include <glib/gfx/window.h>

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

void compositorRenderFrame(gfxContext_t* ctx, gfxWindow_t* windows);
gfxWindow_t* compositorHitTest(gfxWindow_t* windows, int screenX, int screenY);
void dispatchEvent(gfxWindow_t* windows, event_t* ev);
void compositorLoop(gfxContext_t* ctx, gfxWindow_t* windows);