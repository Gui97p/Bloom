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

#include <glib/widgets/label.h>

int main() {
    setupKeyboard();
    setupMouse();
    setupFramebuffer();
    setupThemeFile();

    bloomTheme = themeLoad("/theme.conf");

    gfxContext_t ctx;
    gfxInit(&ctx, fb, fb_info.width, fb_info.height, fb_info.pitch);

    desktop_t desktop;
    desktopInit(&desktop, &ctx);
    gfxWindow_t window;
    gfxCreateWindow(&window, 300, 300, "batata");
    
    label_t label;
    labelInit(&label, &window.container, 10, 10, 100, 30, "Banana");

    while (1) {
        compositorLoop(&ctx, &desktop, &window);
    }
}
