#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/line.h>

static void swapInt(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void sortVertices(
    int* x0, int* y0,
    int* x1, int* y1,
    int* x2, int* y2
) {
    if (*y0 > *y1) {
        swapInt(x0, x1);
        swapInt(y0, y1);
    }
    
    if (*y1 > *y2) {
        swapInt(x1, x2);
        swapInt(y1, y2);
    }
    
    if (*y0 > *y1) {
        swapInt(x0, x1);
        swapInt(y0, y1);
    }
}

void gfxDrawTriangle(gfxSurface_t* surface, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    gfxDrawLine(surface, x0, y0, x1, y1, color);
    gfxDrawLine(surface, x1, y1, x2, y2, color);
    gfxDrawLine(surface, x2, y2, x0, y0, color);
}

void gfxFillTriangle(gfxSurface_t* surface, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    sortVertices(
        &x0, &y0,
        &x1, &y1,
        &x2, &y2
    );

    if (y0 == y2)
        return;
    
    int yStart = y0 < 0 ? 0 : y0;
    int yEnd = y2 >= surface->height ? surface->height - 1 : y2;

    for (int y = yStart; y <= yEnd; y++) {

        int xa =
            x0 +
            (x2 - x0) *
            (y - y0) /
            (y2 - y0);

        int xb;

        if (y < y1) {

            if (y1 == y0)
                xb = x1;
            else
                xb =
                    x0 +
                    (x1 - x0) *
                    (y - y0) /
                    (y1 - y0);

        } else {

            if (y2 == y1)
                xb = x2;
            else
                xb =
                    x1 +
                    (x2 - x1) *
                    (y - y1) /
                    (y2 - y1);
        }

        if (xa > xb)
            swapInt(&xa, &xb);

        gfxDrawHLine(
            surface,
            xa,
            xb,
            y,
            color
        );
    }
}