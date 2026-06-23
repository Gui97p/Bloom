#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>
#include <glib/gfx/line.h>

void gfxDrawCircle(gfxSurface_t* surface, int cx, int cy, int r, uint32_t color) {
    if (cx + r < 0 || cx - r >= surface->width ||
        cy + r < 0 || cy - r >= surface->height)
        return;

    int x = r;
    int y = 0;
    int err = 1 - r;

    while (x >= y) {
        gfxPutPixel(surface, cx + x, cy + y, color);
        gfxPutPixel(surface, cx - x, cy + y, color);
        gfxPutPixel(surface, cx + x, cy - y, color);
        gfxPutPixel(surface, cx - x, cy - y, color);

        gfxPutPixel(surface, cx + y, cy + x, color);
        gfxPutPixel(surface, cx - y, cy + x, color);
        gfxPutPixel(surface, cx + y, cy - x, color);
        gfxPutPixel(surface, cx - y, cy - x, color);

        y++;

        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }

    gfxMarkDirty(surface, cx - r, cy - r, cx + r, cy + r);
}

void gfxFillCircle(gfxSurface_t* surface, int cx, int cy, int r, uint32_t color) {
    int x = r;
    int y = 0;
    int err = 1 - r;

    while (x >= y) {
        gfxDrawHLine(surface, cx - x, cx + x, cy + y, color);
        gfxDrawHLine(surface, cx - x, cx + x, cy - y, color);

        gfxDrawHLine(surface, cx - y, cx + y, cy + x, color);
        gfxDrawHLine(surface, cx - y, cx + y, cy - x, color);

        y++;

        if (err < 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
    
    gfxMarkDirty(surface, cx - r, cy - r, cx + r, cy + r);
}