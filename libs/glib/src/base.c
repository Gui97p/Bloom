#include <string.h>
#include <stdlib.h>

#include <glib/glib.h>
#include <glib/fonts/font.h>

gfxContext_t gfxInit(
    uint32_t* fb,
    uint32_t* bb,
    int width,
    int height,
    int pitch
) {
    gfxContext_t ctx;

    ctx.buffer = fb;
    ctx.backbuffer = bb;
    ctx.width = width;
    ctx.height = height;
    ctx.pitch = pitch;

    return ctx;
}

void gfxBeginFrame(gfxContext_t* ctx) {
    (void)ctx;
}

void gfxEndFrame(gfxContext_t* ctx) {
    memcpy(
        ctx->buffer,
        ctx->backbuffer,
        ctx->width * ctx->height * sizeof(uint32_t)
    );
}

uint32_t getPixel(gfxContext_t* ctx, int x, int y) {
    if (x < 0 || x >= ctx->width)
        return 0;

    if (y < 0 || y >= ctx->height)
        return 0;
    
    return ctx->backbuffer[ctx->width * y + x];
}

void putPixel(gfxContext_t* ctx, int x, int y, uint32_t color) {
    if (x < 0 || x >= ctx->width)
        return;

    if (y < 0 || y >= ctx->height)
        return;
    
    ctx->backbuffer[ctx->width * y + x] = color;
}

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

void drawTriangle(gfxContext_t* ctx, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    drawLine(ctx, x0, y0, x1, y1, color);
    drawLine(ctx, x1, y1, x2, y2, color);
    drawLine(ctx, x2, y2, x0, y0, color);
}

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

void fillTriangle(gfxContext_t* ctx, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
    sortVertices(
        &x0, &y0,
        &x1, &y1,
        &x2, &y2
    );

    if (y0 == y2)
        return;

    for (int y = y0; y <= y2; y++) {

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

        drawHLine(
            ctx,
            xa,
            xb,
            y,
            color
        );
    }
}

void drawChar(gfxContext_t* ctx, font_t* font, int x, int y, char c, uint32_t color)
{
    if (c < font->firstChar || c > font->lastChar) {
        c = '?';
    }

    int index = c - font->firstChar;

    const uint8_t* glyph = (const uint8_t*)font->bitmap + index * font->height * font->bytesPerRow;

    for (int row = 0; row < font->height; row++) {
        for (int col = 0; col < font->width; col++) {
            int byte = col / 8;
            int bit  = 7 - (col % 8);

            if (glyph[row * font->bytesPerRow + byte] & (1 << bit)) {
                putPixel(ctx, x + col, y + row, color);
            }
        }
    }
}

void drawString(gfxContext_t* ctx, font_t* font, int x, int y, const char* str, uint32_t color)
{
    while (*str) {
        drawChar(ctx, font, x, y, *str, color);

        x += 8;
        str++;
    }
}

void blit(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY) {
    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            uint32_t pixel = src->pixels[y * src->width + x];
            
            if (pixel != TRANSPARENT)
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
