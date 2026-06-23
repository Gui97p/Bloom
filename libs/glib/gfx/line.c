#include <stdint.h>
#include <stdlib.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>
#include <glib/gfx/fastops.h>

void gfxDrawHLine(gfxSurface_t* surface, int x0, int x1, int y, uint32_t color) {
    if (y < 0 || y >= surface->height)
        return;

    if (x0 > x1) {
        int t = x0;
        x0 = x1;
        x1 = t;
    }

    if (x0 < 0) x0 = 0;
    if (x1 >= surface->width) x1 = surface->width;
    if (x0 > x1) return;

    fill32(surface->pixels + y * surface->width + x0, color, x1 - x0 + 1);
    
    gfxMarkDirty(surface, x0, y, x1, y);
}

void gfxDrawVLine(gfxSurface_t* surface, int x, int y0, int y1, uint32_t color) {
    if (x < 0 || x >= surface->height)
        return;

    if (y0 > y1) {
        int t = y0;
        y0 = y1;
        y1 = t;
    }

    if (y0 < 0) y0 = 0;
    if (y1 >= surface->height) y1 = surface->height;
    if (y0 > y1) return;

    for (int y = y0; y <= y1; y++) {
        surface->pixels[y * surface->width + x] = color;
    }

    gfxMarkDirty(surface, x, y0, x, y1);
}

void gfxDrawLine(gfxSurface_t* surface, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;

    for(;;){
        gfxPutPixel(surface, x0, y0, color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
    
    gfxMarkDirty(surface, x0, y0, x1, y1);
}