#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void fillCircle(gfxContext_t* ctx, int cx, int cy, int r, uint32_t color);
void drawCircle(gfxContext_t* ctx, int cx, int cy, int r, uint32_t color);