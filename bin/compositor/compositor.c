#include <stdlib.h>

#include <glib/gfx/context.h>
#include <glib/gfx/window.h>
#include <glib/gfx/blit.h>
#include <glib/gfx/rect.h>
#include <glib/gfx/circle.h>
#include <glib/fonts/font.h>

#include <bin/compositor/compositor.h>

#include <bloom/debug.h>

static compositorState_t state;
static int nextZ = 4;

static void sendWindowEvent(gfxWindow_t* win, windowEvent_t ev) {
    if (win && win->onWindowEvent) {
        win->onWindowEvent(win, &ev);
    }
}

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
    gfxWindow_t* sorted[MAX_WINDOWS];
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
        uint32_t barColor = w->focused ? 0x3A6EA5 : 0x555555;
        
        gfxFillRect(&ctx->backbuffer, w->x, w->y, w->surface.width, w->titleBarHeight, barColor);
        gfxDrawString(&ctx->backbuffer, &font8x16, w->x + (w->titleBarHeight / 4), w->y + (w->titleBarHeight / 6), w->title, 0xFFFFFF);
        
        int r = w->titleBarHeight * 0.3;
        gfxFillCircle(&ctx->backbuffer, w->x + w->surface.width - 2 * r, (w->y + w->titleBarHeight / 2), r, 0xFF0000);
        
        if (w->onDraw) w->onDraw(w);
        gfxBlit(&ctx->backbuffer, &w->surface, w->x, w->y + w->titleBarHeight);
    }
}

gfxWindow_t* compositorHitTest(gfxWindow_t* windows, int screenX, int screenY) {
    gfxWindow_t* topHit = NULL;
    int topZ = -1;

    for (gfxWindow_t* w = windows; w; w = w->next) {
        if (!w->visible) continue;

        int totalHeight = w->titleBarHeight + w->surface.height;

        if (screenX >= w->x && screenX < w->x + w->surface.width &&
            screenY >= w->y && screenY < w->y + totalHeight) {
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
            if (target) {    
                int winBottom = target->y + target->titleBarHeight + target->surface.height;
                int winRight = target->x + target->surface.width;

                bool onResizeCorner = ev->mouse.x >= winRight - RESIZE_MARGIN && ev->mouse.y >= winBottom - RESIZE_MARGIN;
            
                bringToFront(windows, target);

                if (target != state.focusedWindow) {
                    if (state.focusedWindow) {
                        state.focusedWindow->focused = false;

                        sendWindowEvent(state.focusedWindow, (windowEvent_t){.type = WINDOW_EVENT_UNFOCUS});
                    }

                    state.focusedWindow = target;

                    if (state.focusedWindow) {
                        state.focusedWindow->focused = true;

                        sendWindowEvent(state.focusedWindow, (windowEvent_t){.type = WINDOW_EVENT_FOCUS});
                    }
                }
                
                bool onTitleBar = ev->mouse.y < target->y + target->titleBarHeight;
                bool onCloseButton = onTitleBar && ev->mouse.x >= target->x + target->surface.width - 24;
                
                if (onCloseButton) {
                    target->visible = false;
                    sendWindowEvent(target, (windowEvent_t){.type = WINDOW_EVENT_CLOSE});
                    if (state.focusedWindow == target) state.focusedWindow = NULL;
                    break;
                }
                
                if (onResizeCorner) {
                    state.resizingWindow = target;
                    state.resizeStartW = target->surface.width;
                    state.resizeStartH = target->surface.height;
                    state.resizeStartMouseX = ev->mouse.x;
                    state.resizeStartMouseY = ev->mouse.y;
                } else if (onTitleBar) {
                    state.dragging = target;
                    state.dragOffsetX = ev->mouse.x - target->x;
                    state.dragOffsetY = ev->mouse.y - target->y;
                } else if (target->onMouseEvent) {
                    mouseEvent_t local = ev->mouse;
                    local.x -= target->x;
                    local.y -= target->y + target->titleBarHeight;
                    target->onMouseEvent(target, &local);
                }
            }
            break;
        }

        case EVENT_MOUSE_MOVE: {
            state.mouseX = ev->mouse.x;
            state.mouseY = ev->mouse.y;

            if (state.resizingWindow) {
                int newW = state.resizeStartW + (ev->mouse.x - state.resizeStartMouseX);
                int newH = state.resizeStartH + (ev->mouse.y - state.resizeStartMouseY);
    
                if (newW < 50) newW = 50;
                if (newH < 50) newH = 50;

                if (abs(newW - state.resizingWindow->surface.width) >= 16 ||
                    abs(newH - state.resizingWindow->surface.height) >= 16) {
                    gfxResizeSurface(&state.resizingWindow->surface, newW, newH);
                    
                    (windowEvent_t){
                        .type = WINDOW_EVENT_RESIZE,
                        .resize = {
                            .width = newW,
                            .height = newH
                        }
                    };
                }
            }

            if (state.dragging) {
                state.dragging->x = ev->mouse.x - state.dragOffsetX;
                state.dragging->y = ev->mouse.y - state.dragOffsetY;
            }

            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target && target->onMouseEvent) {
                mouseEvent_t local = ev->mouse;
                local.x -= target->x;
                local.y -= target->y + target->titleBarHeight;
                target->onMouseEvent(target, &local);
            }
            break;
        }

        case EVENT_MOUSE_UP: {
            state.dragging = NULL;
            state.resizingWindow = NULL;

            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target && target->onMouseEvent) {
                mouseEvent_t local = ev->mouse;
                local.x -= target->x;
                local.y -= target->y + target->titleBarHeight;
                target->onMouseEvent(target, &local);
            }
            break;
        }

        case EVENT_KEY_DOWN:
        case EVENT_KEY_UP:
            if (state.focusedWindow && state.focusedWindow->onKeyEvent) {
                state.focusedWindow->onKeyEvent(state.focusedWindow, &ev->key);
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

    drawCursor(ctx, state.mouseX, state.mouseY);

    gfxEndFrame(ctx);
}
