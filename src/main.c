#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <bin/terminal/terminal.h>
#include <drivers/keyboard/keyboard.h>

#include <glib/gfx/context.h>
#include <glib/buffer.h>

// static uint32_t backbuffer[1280 * 800];

int main() {
    keyboardInit();
    setupFramebuffer();

    gfxContext_t ctx = gfxInit(fb, fb_info.width, fb_info.height, fb_info.pitch);

    termMain(&ctx);

    gfxBeginFrame(&ctx);
    
    

    gfxEndFrame(&ctx);
}
