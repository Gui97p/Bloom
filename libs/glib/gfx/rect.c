#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>

void drawRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color) {
    for (int i = 0; i < width; i++) {
        putPixel(ctx, x + i, y, color);
        putPixel(ctx, x + i, y + height - 1, color);
    }

    for (int i = 0; i < height; i++) {
        putPixel(ctx, x, y + i, color);
        putPixel(ctx, x + width - 1, y + i, color);
    }
}

void fillRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color) {
    for (int py = y; py < y + height; py++) {
        for (int px = x; px < x + width; px++) {
            putPixel(ctx, px, py, color);
        }
    }
}