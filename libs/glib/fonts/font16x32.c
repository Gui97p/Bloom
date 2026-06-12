#include <glib/fonts/font.h>
#include <glib/fonts/bitmap16x32.h>

font_t font16x32 = {
    .bitmap = font16x32bitmap,
    .width = 16,
    .height = 32,
    .firstChar = 32,
    .lastChar = 126,
    .bytesPerRow = 2
};
