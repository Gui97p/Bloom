#include <glib/gfx/context.h>
#include <glib/gfx/window.h>
#include <glib/gfx/blit.h>
#include <glib/gfx/rect.h>

#include <bin/compositor/compositor.h>

#include <bloom/debug.h>

static compositorState_t state;
static gfxWindow_t* focusedWindow = NULL;
static int nextZ = 4;

void compactZIndex(gfxWindow_t* windows) {
    int count = 0;
    for (gfxWindow_t* w = windows; w; w = w->next) count++;

    gfxWindow_t* arr[count];
    int i = 0;
    for (gfxWindow_t* w = windows; w; w = w->next) arr[i++] = w;

    for (int a = 1; a < count; a++) {
        gfxWindow_t* key = arr[a];
        int b = a - 1;
        while (b >= 0 && arr[b]->zIndex > key->zIndex) {
            arr[b + 1] = arr[b];
            b--;
        }
        arr[b + 1] = key;
    }

    for (int j = 0; j < count; j++) {
        arr[j]->zIndex = j + 1;
    }

    nextZ = count + 1;
}

static void bringToFront(gfxWindow_t* windows, gfxWindow_t* win) {
    if (nextZ >= 65535) {
        compactZIndex(windows);
    }
    win->zIndex = nextZ++;
}

void compositorRenderFrame(gfxContext_t* ctx, gfxWindow_t* windows) {
    gfxWindow_t* sorted[8];
    int count = 0;

    for (gfxWindow_t* w = windows; w; w = w->next) {
        if (w->visible) sorted[count++] = w;
    }

    for (int i = 1; i < count; i++) {
        gfxWindow_t* key = sorted[i];
        int j = i - 1;
        while (j >= 0 && sorted[j]->zIndex > key->zIndex) {
            sorted[j + 1] = sorted[j];
            j--;
        }
        sorted[j + 1] = key;
    }

    for (int i = 0; i < count; i++) {
        gfxWindow_t* w = sorted[i];
        if (w->onDraw) w->onDraw(w);
        gfxBlit(&ctx->backbuffer, &w->surface, w->x, w->y);
    }
}

gfxWindow_t* compositorHitTest(gfxWindow_t* windows, int screenX, int screenY) {
    gfxWindow_t* topHit = NULL;
    int topZ = -1;

    for (gfxWindow_t* w = windows; w; w = w->next) {
        if (!w->visible) continue;

        if (screenX >= w->x && screenX < w->x + w->surface.width &&
            screenY >= w->y && screenY < w->y + w->surface.height) {
            if (w->zIndex > topZ) {
                topZ = w->zIndex;
                topHit = w;
            }
        }
    }

    return topHit;
}

void dispatchEvent(gfxWindow_t* windows, event_t* ev) {
    switch (ev->type) {
        case EVENT_MOUSE_DOWN: {
            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target != focusedWindow) {
                if (focusedWindow) focusedWindow->focused = false;
                focusedWindow = target;
                if (focusedWindow) focusedWindow->focused = true;
            }
            
            if (target) {
                bringToFront(windows, target);
                
                state.dragging = target;
                state.dragOffsetX = ev->mouse.x - target->x;
                state.dragOffsetY = ev->mouse.y - target->y;

                if (target->onMouseEvent) {
                    mouseEvent_t local = ev->mouse;
                    local.x -= target->x;
                    local.y -= target->y;
                    target->onMouseEvent(target, &local);
                }
            }
            break;
        }

        case EVENT_MOUSE_MOVE: {
            if (state.dragging) {
                state.dragging->x = ev->mouse.x - state.dragOffsetX;
                state.dragging->y = ev->mouse.y - state.dragOffsetY;
            }

            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target && target->onMouseEvent) {
                mouseEvent_t local = ev->mouse;
                local.x -= target->x;
                local.y -= target->y;
                target->onMouseEvent(target, &local);
            }
            break;
        }

        case EVENT_MOUSE_UP: {
            state.dragging = NULL;

            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target && target->onMouseEvent) {
                mouseEvent_t local = ev->mouse;
                local.x -= target->x;
                local.y -= target->y;
                target->onMouseEvent(target, &local);
            }
            break;
        }

        case EVENT_KEY_DOWN:
        case EVENT_KEY_UP:
            if (focusedWindow && focusedWindow->onKeyEvent) {
                focusedWindow->onKeyEvent(focusedWindow, &ev->key);
            }
            break;
    }
}

void drawCursor(gfxContext_t* ctx, int x, int y) {
    gfxFillRect(
        &ctx->backbuffer,
        x,
        y,
        8,
        8,
        0xFFFFFF
    );
}

void compositorLoop(gfxContext_t* ctx, gfxWindow_t* windows) {
    eventPump();

    event_t ev;
    while (eventPoll(&ev)) {
        dispatchEvent(windows, &ev);
    }

    gfxBeginFrame(ctx);

    gfxFillRect(&ctx->backbuffer, 0, 0, ctx->width, ctx->height, 0x000000);

    compositorRenderFrame(ctx, windows);

    drawCursor(ctx, ev.mouse.x, ev.mouse.y);

    gfxEndFrame(ctx);
}
