#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void fillTriangle(gfxContext_t* ctx, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void drawTriangle(gfxContext_t* ctx, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
