#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void gfxDrawRect(gfxSurface_t* surface, int x, int y, int width, int height, uint32_t color);
void gfxFillRect(gfxSurface_t* surface, int x, int y, int width, int height, uint32_t color);