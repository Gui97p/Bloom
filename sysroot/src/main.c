#include <shell/shell.h>
#include <drivers/keyboard/keyboard.h>

#include <bloom/glib/glib.h>
#include <bloom/glib/buffer.h>

int main() {
    keyboardInit();
    // shell();
    
    gfxContext_t ctx = gfxInit(fb, fb_info->width, fb_info->height, fb_info->pitch);

    fillRect(&ctx, 0, 0, ctx.width, ctx.height, 0x000000);

    drawString(
        &ctx,
        10,
        10,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        0xFFFFFF
    );

    drawString(
        &ctx,
        10,
        30,
        "abcdefghijklmnopqrstuvwxyz",
        0xFFFFFF
    );

    drawString(
        &ctx,
        10,
        50,
        "0123456789",
        0xFFFFFF
    );
}
