#include <stdint.h>
#include <string.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>

void gfxBlit(gfxSurface_t* dst, gfxSurface_t* src, int dstX, int dstY) {
    int x0 = dstX < 0 ? 0 : dstX;
    int y0 = dstY < 0 ? 0 : dstY;
    int x1 = dstX + src->width;
    int y1 = dstY + src->height;

    if (x1 > dst->width)  x1 = dst->width;
    if (y1 > dst->height) y1 = dst->height;

    if (x0 >= x1 || y0 >= y1)
        return;

    int copyWidth = x1 - x0;

    for (int y = y0; y < y1; y++) {
        int srcY = y - dstY;
        uint32_t* srcRow = src->pixels + srcY * src->width + (x0 - dstX);
        uint32_t* dstRow = dst->pixels + y * dst->width + x0;

        memcpy(dstRow, srcRow, copyWidth * sizeof(uint32_t));
    }

    gfxMarkDirty(dst, x0, y0, x1, y1);
}

void gfxBlitTransparent(gfxSurface_t* dst, gfxSurface_t* src, int dstX, int dstY, uint32_t transparentColor) {
    int x0 = dstX < 0 ? 0 : dstX;
    int y0 = dstY < 0 ? 0 : dstY;
    int x1 = dstX + src->width;
    int y1 = dstY + src->height;

    if (x1 > dst->width)  x1 = dst->width;
    if (y1 > dst->height) y1 = dst->height;

    if (x0 >= x1 || y0 >= y1)
        return;

    for (int y = y0; y < y1; y++) {
        int srcY = y - dstY;
        uint32_t* srcRow = src->pixels + srcY * src->width;
        uint32_t* dstRow = dst->pixels + y * dst->width;

        for (int x = x0; x < x1; x++) {
            uint32_t color = srcRow[x - dstX];
            if (color != transparentColor)
                dstRow[x] = color;
        }
    }

    gfxMarkDirty(dst, x0, y0, x1, y1);
}
