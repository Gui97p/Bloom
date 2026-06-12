#include <stdint.h>
#include <stdlib.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>

void drawHLine(gfxContext_t* ctx, int x0, int x1, int y, uint32_t color) {
    if (x0 > x1) {
        int t = x0;
        x0 = x1;
        x1 = t;
    }

    for (int x = x0; x <= x1; x++) {
        putPixel(ctx, x, y, color);
    }
}

void drawVLine(gfxContext_t* ctx, int x, int y0, int y1, uint32_t color) {
    if (y0 > y1) {
        int t = y0;
        y0 = y1;
        y1 = t;
    }

    for (int y = y0; y <= y1; y++) {
        putPixel(ctx, x, y, color);
    }
}

void drawLine(gfxContext_t* ctx, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
        putPixel(ctx, x0, y0, color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}