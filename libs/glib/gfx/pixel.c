#include <stdint.h>
#include <glib/gfx/context.h>

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