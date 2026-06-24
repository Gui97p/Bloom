#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t* pixels;

    int width;
    int height;

    size_t capacity;

    int dx0, dy0;
    int dx1, dy1;
    int hasDirty;
} gfxSurface_t;

typedef struct {
    uint32_t* buffer;
    gfxSurface_t backbuffer;

    int width;
    int height;
    int pitch;    
} gfxContext_t;

void gfxInit(gfxContext_t* ctx, uint32_t* fb, int width, int height, int pitch);
void gfxCreateSurface(gfxSurface_t* surface, int width, int height);
void gfxDestroySurface(gfxSurface_t* surface);
void gfxResizeSurface(gfxSurface_t* surface, int width, int height);

void gfxBeginFrame(gfxContext_t* ctx);
void gfxEndFrame(gfxContext_t* ctx);

static inline void gfxMarkDirty(gfxSurface_t* surface, int x0, int y0, int x1, int y1) {
    if (x0 >= x1 || y0 >= y1)
        return;
    
    if (!surface->hasDirty) {
        surface->dx0 = x0;
        surface->dy0 = y0;
        surface->dx1 = x1;
        surface->dy1 = y1;
        surface->hasDirty = 1;
        return;
    }

    if (x0 < surface->dx0) surface->dx0 = x0;
    if (y0 < surface->dy0) surface->dy0 = y0;
    if (x1 > surface->dx1) surface->dx1 = x1;
    if (y1 > surface->dy1) surface->dy1 = y1;
}
