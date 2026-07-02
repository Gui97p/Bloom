#include <stdlib.h>

#include <glib/gfx/context.h>
#include <glib/containers/window.h>
#include <glib/gfx/blit.h>
#include <glib/gfx/rect.h>
#include <glib/gfx/circle.h>
#include <glib/fonts/font.h>

#include <services/compositor/compositor.h>
#include <services/desktop/desktop.h>

#include <bloom/theme.h>
#include <bloom/debug.h>

static compositorState_t state;
static int nextZ = 0;

static void sendWindowEvent(gfxWindow_t* win, windowEvent_t ev) {
    if (win && win->onWindowEvent) {
        win->onWindowEvent(win, &ev);
    }
}

static void sendWindowInputEvent(gfxWindow_t* win, event_t* ev) {
    if (!win || !win->onEvent)
        return;
    
    event_t local = *ev;
    
    if (ev->type == EVENT_MOUSE_DOWN ||
        ev->type == EVENT_MOUSE_MOVE ||
        ev->type == EVENT_MOUSE_UP) {
        local.mouse.x -= win->x;
        local.mouse.y -= win->y + win->titleBarHeight;
    }
    
    win->onEvent(win, &local);
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

static void compositorDrawWindows(gfxSurface_t* surface, gfxWindow_t* windows) {
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
        
        gfxFillRect(surface, w->x, w->y, w->surface.width, w->titleBarHeight, barColor);
        gfxDrawString(surface, &font8x16, w->x + (w->titleBarHeight / 4), w->y + (w->titleBarHeight / 6), w->title, 0xFFFFFF);
        
        int r = w->titleBarHeight * 0.3;
        gfxFillCircle(surface, w->x + w->surface.width - 2 * r, (w->y + w->titleBarHeight / 2), r, 0xFF0000);
        
        
        if (w->dirty) {
            gfxFillRect(&w->surface, 0, 0, w->surface.width, w->surface.height, w->backgroundColor);
            
            if (w->onDraw) w->onDraw(w);
    
            drawWidgets(w);
            
            w->dirty = false;
        }
        gfxDrawRect(surface, w->x-1, w->y-1, w->surface.width + 2, w->surface.height + w->titleBarHeight + 2, bloomTheme.ui.pallete.borderLight);
        
        gfxBlit(surface, &w->surface, w->x, w->y + w->titleBarHeight);
    }
}

static gfxWindow_t* compositorHitTest(gfxWindow_t* windows, int screenX, int screenY) {
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

static void dispatchEvent(gfxContext_t* ctx, gfxWindow_t* windows, event_t* ev) {
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
                } else if (target->onEvent) {
                    sendWindowInputEvent(target, ev);
                }
            }
            break;
        }

        case EVENT_MOUSE_MOVE: {
            state.lastMouseX = state.mouseX;
            state.lastMouseY = state.mouseY;

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
                    
                    sendWindowEvent(state.resizingWindow, (windowEvent_t){
                        .type = WINDOW_EVENT_RESIZE,
                        .resize = {
                            .width = newW,
                            .height = newH
                        }
                    });
                }
            }

            if (state.dragging) {
                int oldX = state.dragging->x;
                int oldY = state.dragging->y;

                gfxMarkDirty(
                    &ctx->backbuffer,
                    oldX,
                    oldY,
                    oldX + state.dragging->surface.width,
                    oldY + state.dragging->surface.height + state.dragging->titleBarHeight
                );

                state.dragging->x = ev->mouse.x - state.dragOffsetX;
                state.dragging->y = ev->mouse.y - state.dragOffsetY;
                
                gfxMarkDirty(
                    &ctx->backbuffer,
                    state.dragging->x,
                    state.dragging->y,
                    state.dragging->x + state.dragging->surface.width,
                    state.dragging->y + state.dragging->surface.height + state.dragging->titleBarHeight
                );
            }

            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target && target->onEvent) {
                sendWindowInputEvent(target, ev);
            }
            break;
        }

        case EVENT_MOUSE_UP: {
            state.dragging = NULL;
            state.resizingWindow = NULL;

            gfxWindow_t* target = compositorHitTest(windows, ev->mouse.x, ev->mouse.y);
            if (target && target->onEvent) {
                sendWindowInputEvent(target, ev);
            }
            break;
        }

        case EVENT_KEY_DOWN:
        case EVENT_KEY_UP:
            if (state.focusedWindow && state.focusedWindow->onEvent) {
                sendWindowInputEvent(state.focusedWindow, ev);
            }
            break;
    }
}

static void compositorDrawCursor(gfxSurface_t* surface, int x, int y) {
    gfxFillRect(surface, x, y, 8, 8, 0xFFFFFF);
}

void compositorLoop(gfxContext_t* ctx, desktop_t* desktop, gfxWindow_t* windows) {
    eventPump();
    
    event_t ev;
    while (eventPoll(&ev)) {
        dispatchEvent(ctx, windows, &ev);
    }
    
    gfxBeginFrame(ctx);

    gfxFillRect(&ctx->backbuffer, 0, 0, ctx->width, ctx->height, desktop->bg);

    desktopDrawTaskbar(&desktop->taskbar);
    gfxBlit(&ctx->backbuffer, &desktop->taskbar.surface, 0, ctx->height - desktop->taskbar.surface.height);
    
    compositorDrawWindows(&ctx->backbuffer, windows);
    
    compositorDrawCursor(&ctx->backbuffer, state.mouseX, state.mouseY);

    gfxEndFrame(ctx);
}
