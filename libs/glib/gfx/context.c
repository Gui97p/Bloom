#include <string.h>
#include <stdlib.h>
#include <glib/gfx/context.h>

void gfxCreateSurface(gfxSurface_t* surface, int width, int height) {
    surface->width = width;
    surface->height = height;

    surface->pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
}

void gfxDestroySurface(gfxSurface_t* surface) {
    free(surface->pixels);
}

void gfxInit(
    gfxContext_t* ctx,
    uint32_t* fb,
    int width,
    int height,
    int pitch
) {
    ctx->buffer = fb;
    gfxCreateSurface(&ctx->backbuffer, width, height);
    ctx->width = width;
    ctx->height = height;
    ctx->pitch = pitch;
}

void gfxBeginFrame(gfxContext_t* ctx) {
    ctx->backbuffer.hasDirty = 0;
}

void gfxEndFrame(gfxContext_t* ctx) {
    gfxSurface_t* bb = &ctx->backbuffer;

    if (!bb->hasDirty)
        return;

    for (int y = bb->dy0; y < bb->dy1; y++) {
        uint8_t* dst = (uint8_t*)ctx->buffer + y * ctx->pitch + bb->dx0 * sizeof(uint32_t);
        uint8_t* src = (uint8_t*)bb->pixels + y * bb->width * sizeof(uint32_t) + bb->dx0 * sizeof(uint32_t);
        size_t rowBytes = (bb->dx1 - bb->dx0) * sizeof(uint32_t);

        memcpy(dst, src, rowBytes);
    }
}
