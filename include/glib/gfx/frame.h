#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "context.h"

typedef struct {
    bool border;
    int borderSize;
    int borderRadius;
    uint32_t borderColor;
} frameStyle_t;

void gfxDrawFrame(gfxSurface_t* surface, int x, int y, int w, int h, frameStyle_t* style);
