#pragma once

#include <stdint.h>
#include <glib/fonts/font.h>

#define TRANSPARENT 0xFF00FF

typedef struct {
    uint32_t* buffer;
    uint32_t* backbuffer;

    int width;
    int height;
    int pitch;
} gfxContext_t;

typedef struct {
    int width;
    int height;
    uint32_t* pixels;
} bitmap_t;

gfxContext_t gfxInit(
    uint32_t* fb,
    uint32_t* bb,
    int width,
    int height,
    int pitch
);

void gfxBeginFrame(gfxContext_t* ctx);
void gfxEndFrame(gfxContext_t* ctx);

uint32_t getPixel(gfxContext_t* ctx, int x, int y);
void putPixel(gfxContext_t* ctx, int x, int y, uint32_t color);

void drawHLine(gfxContext_t* ctx, int x0, int x1, int y, uint32_t color);
void drawVLine(gfxContext_t* ctx, int x, int y0, int y1, uint32_t color);
void drawLine(gfxContext_t* ctx, int x1, int x2, int y1, int y2, uint32_t color);

void drawRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color);
void fillRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color);

void fillCircle(gfxContext_t* ctx, int cx, int cy, int r, uint32_t color);
void drawCircle(gfxContext_t* ctx, int cx, int cy, int r, uint32_t color);

void fillTriangle(gfxContext_t* ctx, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void drawTriangle(gfxContext_t* ctx, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void drawChar(gfxContext_t* ctx, font_t* font, int x, int y, char c, uint32_t color);
void drawString(gfxContext_t* ctx, font_t* font, int x, int y, const char* str, uint32_t color);

void blit(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY);
void blitRegion(gfxContext_t* ctx, bitmap_t* src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY);
void blitScaled(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, int dstW, int dstH);

void blitTransparent(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, uint32_t transparentColor);
void blitRegionTransparent(gfxContext_t* ctx, bitmap_t* src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, uint32_t transparentColor);
void blitScaledTransparent(gfxContext_t* ctx, bitmap_t* src, int dstX, int dstY, int dstW, int dstH, uint32_t transparentColor);