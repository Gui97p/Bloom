#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

uint32_t gfxGetPixel(gfxSurface_t* surface, int x, int y);
void gfxPutPixel(gfxSurface_t* surface, int x, int y, uint32_t color);