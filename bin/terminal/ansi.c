#include <stdlib.h>
#include <bin/terminal/terminal.h>
#include <bloom/debug.h>

void ansiExecute(terminal_t* term, const char *params, char command) {
    ASSERT(params != NULL);
    
    int code = atoi(params);

    switch (command) {
        case 'm': {
            switch (code) {
                case 0:
                    term->currentFg = term->theme->fg_primary;
                    term->currentBg = term->theme->bg_deep;
                    break;

                case 31:
                    term->currentFg = 0xFF0000;
                    break;

                case 32:
                    term->currentFg = 0x00FF00;
                    break;

                case 33:
                    term->currentFg = 0xFFFF00;
                    break;

                case 34:
                    term->currentFg = 0x0000FF;
                    break;

                case 35:
                    term->currentFg = 0xFF00FF;
                    break;

                case 36:
                    term->currentFg = 0x00FFFF;
                    break;

                case 37:
                    term->currentFg = 0xFFFFFF;
                    break;
                
                case 200:
                    term->currentBg = term->theme->bg_deep;
                    break;
                
                case 201:
                    term->currentBg = term->theme->bg_surface;
                    break;
                
                case 300:
                    term->currentFg = term->theme->fg_primary;
                    break;

                case 301:
                    term->currentFg = term->theme->fg_dim;
                    break;
                
                case 302:
                    term->currentFg = term->theme->accent_purple;
                    break;
                
                case 303:
                    term->currentFg = term->theme->accent_bright;
                    break;

                case 304:
                    term->currentFg = term->theme->accent_teal;
                    break;

                case 305:
                    term->currentFg = term->theme->accent_gold;
                    break;

                case 306:
                    term->currentFg = term->theme->accent_pink;
                    break;
            }
            break;
        }

        case 'J': {
            if (code == 2)
                termClear(term);
            break;
        }

        case 'H': {
            term->cursorX = 0;
            term->cursorY = 0;
            break;
        }
    }
}
