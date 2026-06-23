#include <stdint.h>
#include <glib/gfx/context.h>

uint32_t gfxGetPixel(gfxSurface_t* surface, int x, int y) {
    if (x < 0 || x >= surface->width)
        return 0;

    if (y < 0 || y >= surface->height)
        return 0;
    
    return surface->pixels[surface->width * y + x];
}

void gfxPutPixel(gfxSurface_t* surface, int x, int y, uint32_t color) {
    if (x < 0 || x >= surface->width)
        return;

    if (y < 0 || y >= surface->height)
        return;
    
    surface->pixels[surface->width * y + x] = color;
    gfxMarkDirty(surface, x, y, x + 1, y + 1);
}
