#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void drawHLine(gfxContext_t* ctx, int x0, int x1, int y, uint32_t color);
void drawVLine(gfxContext_t* ctx, int x, int y0, int y1, uint32_t color);
void drawLine(gfxContext_t* ctx, int x1, int x2, int y1, int y2, uint32_t color);