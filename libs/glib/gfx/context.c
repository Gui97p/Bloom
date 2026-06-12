#include <glib/gfx/context.h>
#include <string.h>

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