#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <bin/console/console.h>
#include <bin/compositor/compositor.h>

#include <bloom/theme.h>
#include <bloom/debug.h>

#include <glib/gfx/context.h>
#include <glib/gfx/line.h>
#include <glib/gfx/blit.h>
#include <glib/gfx/rect.h>
#include <glib/buffer.h>
#include <glib/fonts/font.h>
#include <glib/input/keyboard.h>
#include <glib/input/mouse.h>

static uint32_t colorA = 0xFF4040; // vermelho
static uint32_t colorB = 0x40FF40; // verde
static uint32_t colorC = 0x4040FF; // azul

void drawSolid(gfxWindow_t* win) {
    gfxFillRect(&win->surface, 0, 0, win->surface.width, win->surface.height, *(uint32_t*)win->userData);
}

void onClickToggle(gfxWindow_t* win, mouseEvent_t* ev) {
    (void)ev;
    uint32_t* color = (uint32_t*)win->userData;
    *color = (*color == colorB) ? 0xFFFF00 : colorB; // alterna verde <-> amarelo
}

void setupWindows(gfxWindow_t* windows) {
    // janela A: vermelha, sem interação, fica atrás
    gfxCreateSurface(&windows[0].surface, 200, 150);
    windows[0].x = 50;
    windows[0].y = 50;
    windows[0].zIndex = 1;
    windows[0].visible = true;
    windows[0].focused = false;
    windows[0].onDraw = drawSolid;
    windows[0].onMouseEvent = NULL;
    windows[0].onKeyEvent = NULL;
    windows[0].userData = &colorA;
    windows[0].next = &windows[1];

    // janela B: verde, clicável (muda de cor ao clicar) — sobrepõe a A
    gfxCreateSurface(&windows[1].surface, 200, 150);
    windows[1].x = 150;
    windows[1].y = 100;
    windows[1].zIndex = 2;
    windows[1].visible = true;
    windows[1].focused = false;
    windows[1].onDraw = drawSolid;
    windows[1].onMouseEvent = onClickToggle;
    windows[1].onKeyEvent = NULL;
    windows[1].userData = &colorB;
    windows[1].next = &windows[2];

    // janela C: azul, mais à frente ainda — testa hit-test/z-order
    gfxCreateSurface(&windows[2].surface, 150, 100);
    windows[2].x = 220;
    windows[2].y = 130;
    windows[2].zIndex = 3;
    windows[2].visible = true;
    windows[2].focused = false;
    windows[2].onDraw = drawSolid;
    windows[2].onMouseEvent = NULL;
    windows[2].onKeyEvent = NULL;
    windows[2].userData = &colorC;
    windows[2].next = NULL;
}

int main() {
    setupKeyboard();
    setupMouse();
    setupFramebuffer();
    setupThemeFile();

    gfxContext_t ctx;
    gfxInit(&ctx, fb, fb_info.width, fb_info.height, fb_info.pitch);

    gfxWindow_t windows[8];
    setupWindows(windows);

    while (1) {
        compositorLoop(&ctx, windows);
    }
}
