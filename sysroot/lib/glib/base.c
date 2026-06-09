#include <bloom/glib/glib.h>
#include <bloom/glib/font8x16.h>

int abs(int x) {
    return x < 0 ? -x : x;
}

gfxContext_t gfxInit(
    uint32_t* fb,
    int width,
    int height,
    int pitch
) {
    gfxContext_t ctx;

    ctx.buffer = fb;
    ctx.width = width;
    ctx.height = height;
    ctx.pitch = pitch;

    return ctx;
}

void putPixel(gfxContext_t* ctx, int x, int y, uint32_t color) {
    if (x < 0 || x >= ctx->width)
        return;

    if (y < 0 || y >= ctx->height)
        return;
    
    ctx->buffer[(ctx->pitch/4) * y + x] = color;
}

void drawLine(gfxContext_t* ctx, int x0, int x1, int y0, int y1, uint32_t color) {
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

void drawChar(
    gfxContext_t* ctx,
    int x,
    int y,
    char c,
    uint32_t color
)
{
    uint8_t* glyph = font8x16[(unsigned char)c];

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 8; col++) {

            if (glyph[row] & (1 << (7 - col))) {
                putPixel(
                    ctx,
                    x + col,
                    y + row,
                    color
                );
            }
        }
    }
}

void drawString(
    gfxContext_t* ctx,
    int x,
    int y,
    const char* str,
    uint32_t color
)
{
    while (*str) {
        drawChar(ctx, x, y, *str, color);

        x += 8;
        str++;
    }
}