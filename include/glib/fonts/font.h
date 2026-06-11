#pragma once

typedef struct {
    const void* bitmap;

    int width;
    int height;

    int firstChar;
    int lastChar;

    int bytesPerRow;
} font_t;

extern font_t font8x16;
extern font_t font16x32;
