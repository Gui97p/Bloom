#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void gfxDrawHLine(gfxSurface_t* surface, int x0, int x1, int y, uint32_t color);
void gfxDrawVLine(gfxSurface_t* surface, int x, int y0, int y1, uint32_t color);
void gfxDrawLine(gfxSurface_t* surface, int x1, int x2, int y1, int y2, uint32_t color);