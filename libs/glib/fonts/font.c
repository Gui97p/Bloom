#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/gfx/pixel.h>
#include <glib/fonts/font.h>

void drawChar(gfxContext_t* ctx, font_t* font, int x, int y, char c, uint32_t color)
{
    if (c < font->firstChar || c > font->lastChar) {
        c = '?';
    }

    int index = c - font->firstChar;

    const uint8_t* glyph = (const uint8_t*)font->bitmap + index * font->height * font->bytesPerRow;

    for (int row = 0; row < font->height; row++) {
        const uint8_t* rowData = glyph + row * font->bytesPerRow;

        for (int col = 0; col < font->width; col++) {
            int byte = font->bytesPerRow - 1 - (col / 8);
            int bit  = 7 - (col % 8);

            if (rowData[byte] & (1 << bit)) {
                putPixel(ctx, x + col, y + row, color);
            }
        }
    }
}

void drawString(gfxContext_t* ctx, font_t* font, int x, int y, const char* str, uint32_t color)
{
    while (*str) {
        drawChar(ctx, font, x, y, *str, color);

        x += font->width;
        str++;
    }
}
