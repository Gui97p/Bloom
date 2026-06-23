#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

void gfxBlit(gfxSurface_t* dst, gfxSurface_t* src, int dstX, int dstY);
void gfxBlitTransparent(gfxSurface_t* dst, gfxSurface_t* src, int dstX, int dstY, uint32_t transparentColor);

// void blit(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY);
// void blitRegion(gfxContext_t* ctx, bitmap_t* src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY);
// void blitScaled(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, int dstW, int dstH);

// void blitTransparent(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, uint32_t transparentColor);
// void blitRegionTransparent(gfxContext_t* ctx, bitmap_t* src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, uint32_t transparentColor);
// void blitScaledTransparent(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, int dstW, int dstH, uint32_t transparentColor);
