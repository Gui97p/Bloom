#pragma once

#include <stdint.h>

typedef struct {
    uint32_t* buffer;
    int width;
    int height;
    int pitch;
} gfxContext_t;

gfxContext_t gfxInit(
    uint32_t* fb,
    int width,
    int height,
    int pitch
);

void putPixel(gfxContext_t* ctx, int x, int y, uint32_t color);

void drawLine(gfxContext_t* ctx, int x1, int x2, int y1, int y2, uint32_t color);

void drawRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color);

void fillRect(gfxContext_t* ctx, int x, int y, int width, int height, uint32_t color);

void drawChar(gfxContext_t* ctx, int x, int y, char c, uint32_t color);

void drawString(gfxContext_t* ctx, int x, int y, const char* str, uint32_t color);