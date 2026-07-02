#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#include <glib/gfx/context.h>
#include <glib/gfx/rect.h>
#include <glib/fonts/font.h>
#include <glib/gfx/blit.h>
#include <glib/input/event.h>
#include <glib/input/mouse.h>

#include <apps/terminal/terminal.h>
#include <apps/shell/shell.h>
#include <apps/console/readline.h>

#include <bloom/version.h>
#include <bloom/theme.h>
#include <bloom/debug.h>

#include "footer.h"
#include "boot.h"

void consoleMain(gfxContext_t* ctx) {
    DPRINTF("[CONSOLE] Starting Console\n");

    terminal_t term;
    gfxSurface_t termSurface, footer;
    bloomTheme_t theme = themeLoad("theme.conf");

    gfxCreateSurface(&termSurface, ctx->width, ctx->height);
    gfxCreateSurface(&footer, ctx->width, 48);
    termInit(&term, &termSurface, &theme);

    DPRINTF("[CONSOLE] Drawing Footer\n");

    drawFooter(&footer, &theme);

    consoleBoot(ctx);

    readline_t rl;
    readlineInit(&rl);

    shellPrompt();
    
    DPRINTF("[CONSOLE] Starting Shell\n");
    
    int n;
    char buf[128];
    while (1) {
        while ((n = fread(buf, 1, sizeof(buf)-1, stdout)) > 0) {
            buf[n] = '\0';
            
            termWrite(&term, buf);
        }

        event_t ev;

        while (eventPoll(&ev)) {
            if (ev.type == EVENT_KEY_DOWN) {
                if (readlineFeed(&rl, &term, &ev.key)) {
                    if (*rl.line != '\0') {
                        shellExecute(&term, rl.line);
                        putchar('\n');
                    }
    
                    readlineInit(&rl);
    
                    shellPrompt();
                }
            } else if (ev.type == EVENT_MOUSE_MOVE) {
                DPRINTF("MOVEEEEEEEEE\n");
            }
        }

        fflush(stdout);

        termFlush(&term);
        gfxBlit(&ctx->backbuffer, &termSurface, 0, 0);
        gfxBlit(&ctx->backbuffer, &footer, 0, term.surface->height - 48);

        gfxEndFrame(ctx);
    }
}
