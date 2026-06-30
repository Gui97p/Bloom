#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <services/compositor/compositor.h>
#include <services/desktop/desktop.h>

#include <bloom/theme.h>
#include <bloom/debug.h>

#include <glib/buffer.h>
#include <glib/gfx/context.h>

int main() {
    setupKeyboard();
    setupMouse();
    setupFramebuffer();
    setupThemeFile();

    gfxContext_t ctx;
    gfxInit(&ctx, fb, fb_info.width, fb_info.height, fb_info.pitch);

    desktop_t desktop;
    desktopInit(&desktop, &ctx);

    while (1) {
        compositorLoop(&ctx, &desktop);
    }
}
