#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <bin/console/console.h>
#include <drivers/keyboard/keyboard.h>
#include <bloom/theme.h>

#include <glib/gfx/context.h>
#include <glib/buffer.h>
#include <glib/fonts/font.h>

// static uint32_t backbuffer[1280 * 800];

int main() {
    keyboardInit();
    setupFramebuffer();
    setupThemeFile();

    gfxContext_t ctx = gfxInit(fb, fb_info.width, fb_info.height, fb_info.pitch);

    consoleMain(&ctx);

    gfxBeginFrame(&ctx);
    
    

    gfxEndFrame(&ctx);
}
