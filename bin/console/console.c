#include <glib/gfx/context.h>
#include <bin/terminal/terminal.h>
#include <bin/shell/shell.h>

void consoleMain(gfxContext_t* ctx) {
    terminal_t term;
    termInit(&term, ctx);
    
    shellMain(&term);
}
