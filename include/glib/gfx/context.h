#pragma once

#include <stdint.h>

typedef struct {
    uint32_t* buffer;
    uint32_t* backbuffer;

    int width;
    int height;
    int pitch;
} gfxContext_t;

gfxContext_t gfxInit(uint32_t* fb, uint32_t* bb, int width, int height, int pitch);

void gfxBeginFrame(gfxContext_t* ctx);
void gfxEndFrame(gfxContext_t* ctx);