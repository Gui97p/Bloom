#include <string.h>
#include <stdlib.h>
#include <glib/gfx/context.h>

gfxContext_t gfxInit(
    uint32_t* fb,
    int width,
    int height,
    int pitch
) {
    gfxContext_t ctx;
    uint32_t *bb = (uint32_t*)malloc(width * height * sizeof(uint32_t));

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