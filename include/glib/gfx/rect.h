#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void drawRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color);
void fillRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color);