#include <glib/fonts/font.h>
#include <glib/fonts/bitmap8x16.h>
#include <glib/fonts/bitmap16x32.h>

font_t font8x16 = {
    .bitmap = font8x16bitmap,
    .width = 8,
    .height = 16,
    .firstChar = 32,
    .lastChar = 126,
    .bytesPerRow = 1
};

font_t font16x32 = {
    .bitmap = font16x32bitmap,
    .width = 16,
    .height = 32,
    .firstChar = 32,
    .lastChar = 126,
    .bytesPerRow = 2
};
