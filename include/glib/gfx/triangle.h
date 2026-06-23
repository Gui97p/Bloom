#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void gfxFillTriangle(gfxSurface_t* surface, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void gfxDrawTriangle(gfxSurface_t* surface, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
