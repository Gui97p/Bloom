#include <string.h>
#include <glib/gfx/context.h>
#include <glib/gfx/rect.h>
#include <glib/fonts/font.h>
#include <bloom/theme.h>

static int drawFooterSegment(gfxSurface_t* surface, font_t* font, int x, int y,
                              const char* str, uint32_t color) {
    gfxDrawString(surface, font, x, y, str, color);
    return x + strlen(str) * font->width;
}

void drawFooter(gfxSurface_t* footer, bloomTheme_t* theme) {
    font_t* font = &font16x32;
    int x = 0;

    gfxFillRect(footer, 0, 0, footer->width, footer->height, theme->bg_surface);

#define SEG(str, color) x = drawFooterSegment(footer, font, x, 8, str, color)

    SEG(" BLOOM",           theme->accent_bright);
    SEG(" | uptime ",      theme->fg_dim);
    SEG("00:04:12",          theme->fg_primary);
    SEG(" | mem ",         theme->fg_dim);
    SEG("14 / 125mb",        theme->accent_bright);
    SEG(" | x64 | Sekura ",      theme->fg_dim);
    SEG("v0.1.0 Genesis",   theme->accent_bright);
    SEG(" | ", theme->fg_dim);
    SEG("21:46",             theme->accent_bright);

#undef SEG
}
