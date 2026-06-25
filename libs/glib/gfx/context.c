#include <string.h>
#include <stdlib.h>

#include <glib/gfx/context.h>

#include <bloom/debug.h>

void gfxCreateSurface(gfxSurface_t* surface, int width, int height) {
    surface->width = width;
    surface->height = height;
    surface->capacity = width * height;

    surface->pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
}

void gfxDestroySurface(gfxSurface_t* surface) {
    free(surface->pixels);
}

void gfxResizeSurface(gfxSurface_t* surface, int width, int height) {
    if (width < 1) width = 1;
    if (height < 1) height = 1;
    if (width > 4096) width = 4096;
    if (height > 4096) height = 4096;

    if (width == surface->width && height == surface->height) return;

    size_t needed = (size_t)width * (size_t)height;

    if (needed > surface->capacity) {
        size_t newCapacity = surface->capacity * 2;
        if (newCapacity < needed) newCapacity = needed;

        uint32_t* newPixels = (uint32_t*)malloc(newCapacity * sizeof(uint32_t));
        ASSERT(newPixels);
        free(surface->pixels);

        surface->pixels = newPixels;
        surface->capacity = newCapacity;
    }

    surface->width = width;
    surface->height = height;
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
