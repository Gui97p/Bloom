#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void gfxFillCircle(gfxSurface_t* surface, int cx, int cy, int r, uint32_t color);
void gfxDrawCircle(gfxSurface_t* surface, int cx, int cy, int r, uint32_t color);