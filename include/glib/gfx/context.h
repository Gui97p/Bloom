#pragma once

#include <stdint.h>

typedef struct {
    uint32_t* buffer;
    uint32_t* backbuffer;

    int width;
    int height;
    int pitch;
} gfxContext_t;

typedef struct {
    gfxContext_t *ctx;
    
    int x;
    int y;

    int width;
    int height;
} gfxSurface_t;

gfxContext_t gfxInit(uint32_t* fb, int width, int height, int pitch);

void gfxBeginFrame(gfxContext_t* ctx);
void gfxEndFrame(gfxContext_t* ctx);