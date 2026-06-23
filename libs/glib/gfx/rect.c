#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/line.h>
#include <glib/gfx/fastops.h>

void gfxDrawRect(gfxSurface_t* surface, int x, int y, int width, int height, uint32_t color) {
    gfxDrawHLine(surface, x, x + width - 1, y, color);
    gfxDrawHLine(surface, x, x + width - 1, y + height - 1, color);
    gfxDrawVLine(surface, y, y + height - 1, x, color);
    gfxDrawVLine(surface, y, y + height - 1, x + width - 1, color);
}

void gfxFillRect(gfxSurface_t* surface, int x, int y, int width, int height, uint32_t color) {
    int x0 = x < 0 ? 0 : x;
    int y0 = y < 0 ? 0 : y;
    int x1 = x + width;
    int y1 = y + height;

    if (x1 > surface->width)  x1 = surface->width;
    if (y1 > surface->height) y1 = surface->height;

    if (x0 >= x1 || y0 >= y1)
        return;
    
    for (int py = y0; py < y1; py++) {
        fill32(surface->pixels + py * surface->width + x0, color, x1 - x0);
    }

    gfxMarkDirty(surface, x0, y0, x1, y1);
}
