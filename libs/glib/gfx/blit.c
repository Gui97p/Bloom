#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>
#include <glib/bitmap/bitmap.h>

void blit(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY) {
    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            uint32_t pixel = src->pixels[y * src->width + x];
            
            putPixel(ctx, dstX + x, dstY + y, pixel);
        }
    }
}

void blitRegion(gfxContext_t* ctx, bitmap_t* src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY) {
    for (int y = 0; y < srcH; y++) {
        for (int x = 0; x < srcW; x++) {
            uint32_t color =
                src->pixels[
                    (srcY + y) * src->width +
                    (srcX + x)
                ];

            putPixel(
                ctx,
                dstX + x,
                dstY + y,
                color
            );
        }
    }
}

void blitScaled(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, int dstW, int dstH) {
    for (int y = 0; y < dstH; y++) {
        for (int x = 0; x < dstW; x++) {

            int srcX =
                x * src->width / dstW;

            int srcY =
                y * src->height / dstH;

            uint32_t color =
                src->pixels[
                    srcY * src->width +
                    srcX
                ];

            putPixel(
                ctx,
                dstX + x,
                dstY + y,
                color
            );
        }
    }
}

void blitTransparent(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, uint32_t transparentColor) {
    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            uint32_t color =
                src->pixels[
                    y * src->width + x
                ];

            if (color == transparentColor)
                continue;

            putPixel(
                ctx,
                dstX + x,
                dstY + y,
                color
            );
        }
    }
}

void blitRegionTransparent(gfxContext_t* ctx, bitmap_t* src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, uint32_t transparentColor) {
    for (int y = 0; y < srcH; y++) {
        int sy = srcY + y;

        if (sy < 0 || sy >= src->height)
            continue;

        for (int x = 0; x < srcW; x++) {
            int sx = srcX + x;

            if (sx < 0 || sx >= src->width)
                continue;

            uint32_t color =
                src->pixels[
                    sy * src->width + sx
                ];

            if (color == transparentColor)
                continue;

            putPixel(
                ctx,
                dstX + x,
                dstY + y,
                color
            );
        }
    }
}

void blitScaledTransparent(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, int dstW, int dstH, uint32_t transparentColor) {
    for (int y = 0; y < dstH; y++) {
        for (int x = 0; x < dstW; x++) {
            int srcX = x * src->width  / dstW;
            int srcY = y * src->height / dstH;

            uint32_t color =
                src->pixels[
                    srcY * src->width + srcX
                ];

            if (color == transparentColor)
                continue;

            putPixel(
                ctx,
                dstX + x,
                dstY + y,
                color
            );
        }
    }
}