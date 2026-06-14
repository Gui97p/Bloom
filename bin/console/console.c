#include <glib/gfx/context.h>
#include <bin/terminal/terminal.h>
#include <bin/shell/shell.h>
#include <bloom/theme.h>

#include <stdio.h>
void consoleMain(gfxContext_t* ctx) {
    terminal_t term;
    gfxSurface_t termSurface = {.ctx = ctx};
    termInit(&term, ctx, &termSurface);

    bloomTheme_t theme = themeLoad("theme.conf");
    termApplyTheme(&term, &theme);
    
    shellMain(&term, &theme);
}
