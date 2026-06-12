#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

uint32_t getPixel(gfxContext_t* ctx, int x, int y);
void putPixel(gfxContext_t* ctx, int x, int y, uint32_t color);