#include <glib/fonts/font.h>
#include <glib/fonts/bitmap8x16.h>

font_t font8x16 = {
    .bitmap = font8x16bitmap,
    .width = 8,
    .height = 16,
    .firstChar = 32,
    .lastChar = 126,
    .bytesPerRow = 1
};
