#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>
#include <glib/gfx/line.h>

void drawCircle(gfxContext_t* ctx, int cx, int cy, int r, uint32_t color) {
    int x = r;
    int y = 0;
    int err = 1 - r;

    while (x >= y) {
        putPixel(ctx, cx + x, cy + y, color);
        putPixel(ctx, cx - x, cy + y, color);
        putPixel(ctx, cx + x, cy - y, color);
        putPixel(ctx, cx - x, cy - y, color);

        putPixel(ctx, cx + y, cy + x, color);
        putPixel(ctx, cx - y, cy + x, color);
        putPixel(ctx, cx + y, cy - x, color);
        putPixel(ctx, cx - y, cy - x, color);

        y++;

        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}

void fillCircle(gfxContext_t* ctx, int cx, int cy, int r, uint32_t color) {
    int x = r;
    int y = 0;
    int err = 1 - r;

    while (x >= y) {
        drawHLine(ctx, cx - x, cx + x, cy + y, color);
        drawHLine(ctx, cx - x, cx + x, cy - y, color);

        drawHLine(ctx, cx - y, cx + y, cy + x, color);
        drawHLine(ctx, cx - y, cx + y, cy - x, color);

        y++;

        if (err < 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
        }
    }
}