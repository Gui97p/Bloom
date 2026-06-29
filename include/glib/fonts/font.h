#pragma once

#include <stdint.h>
#include <glib/gfx/context.h>

typedef struct {
    const uint8_t* bitmap;

    int width;
    int height;

    int firstChar;
    int lastChar;

    int bytesPerRow;
} font_t;

extern font_t font8x16;
extern font_t font16x32;

void gfxDrawChar(gfxSurface_t* surface, font_t* font, int x, int y, char c, uint32_t color);
void gfxDrawString(gfxSurface_t* surface, font_t* font, int x, int y, const char* str, uint32_t color);
int gfxMeasureString(font_t* font, int lenght);