#include <bin/terminal/terminal.h>
#include <drivers/keyboard/keyboard.h>
#include <stdio.h>

#include <glib/glib.h>
#include <glib/buffer.h>

static uint32_t backbuffer[1280 * 800];

int main() {
    keyboardInit();

    printf("%d %d %d", fb_info->width, fb_info->height, fb_info->pitch);

    gfxContext_t ctx = gfxInit(fb, fb_info->width, fb_info->height, fb_info->pitch);
    ctx.backbuffer = backbuffer;

    terminalMain(&ctx);
}
