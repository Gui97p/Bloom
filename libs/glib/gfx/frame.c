#include <glib/gfx/frame.h>
#include <glib/gfx/rect.h>

void gfxDrawFrame(gfxSurface_t* surface, int x, int y, int w, int h, frameStyle_t* style) {
    int bs = style->borderSize;

    if (style->border) {
        for (int i = 0; i < bs; i++) {
            gfxDrawRect(surface, x + i, y + i, w - i, h - i, style->borderColor);
        }
    }
}
