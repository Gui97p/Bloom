#include <stdint.h>
#include <glib/gfx/context.h>
#include <glib/fonts/font.h>
#include <bloom/debug.h>

void gfxDrawChar(gfxSurface_t* surface, font_t* font, int x, int y, char c, uint32_t color)
{
    ASSERT(font->width % 8 == 0);
    
    if (c < font->firstChar || c > font->lastChar) {
        c = '?';
    }

    if (x + font->width <= 0 || x >= surface->width ||
        y + font->height <= 0 || y >= surface->height)
        return;

    int index = c - font->firstChar;
    const uint8_t* glyph = (const uint8_t*)font->bitmap + index * font->height * font->bytesPerRow;

    int rowStart = (y < 0) ? -y : 0;
    int rowEnd = font->height;
    if (y + rowEnd > surface->height) rowEnd = surface->height - y;

    int colStart = (x < 0) ? -x : 0;
    int colEnd = font->width;
    if (x + colEnd > surface->width) colEnd = surface->width - x;

    for (int row = rowStart; row < rowEnd; row++) {
        const uint8_t* rowData = glyph + row * font->bytesPerRow;

        int blank = 1;
        for (int b = 0; b < font->bytesPerRow; b++) {
            if (rowData[b] != 0) {
                blank = 0;
                break;
            }
        }
        if (blank) continue;

        uint32_t* destRow = surface->pixels + (y + row) * surface->width;

        for (int col = colStart; col < colEnd; col++) {
            int byte = font->bytesPerRow - 1 - (col / 8);
            int bit  = 7 - (col % 8);

            if (rowData[byte] & (1 << bit)) {
                destRow[x + col] = color;
            }
        }
    }

    gfxMarkDirty(surface, x + colStart, y + rowStart, colEnd - colStart, rowEnd - rowStart);
}

void gfxDrawString(gfxSurface_t* surface, font_t* font, int x, int y, const char* str, uint32_t color)
{
    if (y + font->height <= 0 || y >= surface->height)
        return;

    while (*str) {
        if (x >= surface->width)
            break;

        gfxDrawChar(surface, font, x, y, *str, color);

        x += font->width;
        str++;
    }
}
