#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <bin/terminal/terminal.h>
#include <bin/console/readline.h>
#include <bin/shell/builtins.h>
#include <glib/input/event.h>

static char historyBuffer[HISTORY_SIZE][MAX_CMD_LEN];
static int historyCount = 0;
static int historyPos = -1;

void readlineInit(readline_t* rl) {
    memset(rl, 0, sizeof(*rl));
    rl->historyPos = -1;
}

void historyAdd(const char* cmd) {
    if (cmd[0] == '\0')
        return;
    
        if (historyCount > 0 && strcmp(historyBuffer[(historyCount-1) % HISTORY_SIZE], cmd) == 0)
            return;
        
        strncpy(historyBuffer[historyCount % HISTORY_SIZE], cmd, MAX_CMD_LEN-1);
        historyBuffer[historyCount % HISTORY_SIZE][MAX_CMD_LEN-1] = '\0';
        historyCount++;
}

static void clearLine(terminal_t* term, int len) {
    for (int i = 0; i < len; i ++) {
        termPutChar(term, '\b', term->currentFg, term->currentBg);
    }
}

bool readlineFeed(readline_t* rl, terminal_t* term, keyEvent_t* ev) {
    if (!ev->pressed)
        return false;
    
    term->cursorVisible = true;
    term->cursorCounter = 0;
    
    size_t size = sizeof(rl->line);
    
    switch (ev->key) {
        case KEY_UP: {
            int next = historyPos + 1;
            int maxPos = historyCount > HISTORY_SIZE ? HISTORY_SIZE : historyCount;
            if (next >= maxPos)
                return false;
            
            if (historyPos == -1) {
                rl->line[rl->pos] = '\0';
                strncpy(rl->tmp, rl->line, MAX_CMD_LEN - 1);
                rl->tmp[MAX_CMD_LEN - 1] = '\0';
            }

            historyPos = next;
            int idx = (historyCount - 1 - historyPos + HISTORY_SIZE) % HISTORY_SIZE;

            clearLine(term, rl->pos);
            strncpy(rl->line, historyBuffer[idx], size - 1);
            rl->line[size - 1] = '\0';
            rl->pos = strlen(rl->line);
            if (rl->pos >= size) rl->pos = size - 1;

            printf("%s", rl->line);

            return false;
        }
        
        case KEY_DOWN: {
            if (historyPos == -1)
                return false;

            historyPos--;

            clearLine(term, rl->pos);

            if (historyPos == -1) {
                strncpy(rl->line, rl->tmp, size - 1);
            } else {
                int idx = (historyCount - 1 - historyPos + HISTORY_SIZE) % HISTORY_SIZE;
                strncpy(rl->line, historyBuffer[idx], size - 1);
            }

            rl->line[size - 1] = '\0';
            rl->pos = strlen(rl->line);
            
            printf("%s", rl->line);

            return false;
        }

        case KEY_TAB: {
            for (int i = 0; i < builtinsCount; i++) {
                if (strncmp(rl->line, builtins[i].name, rl->pos) == 0 && rl->pos != 0) {
                    int len = strlen(builtins[i].name);
                    strcpy(rl->line, builtins[i].name);
                    rl->pos = len;
                    break;
                }
            }

            return false;
        }

        default:
            break;
    }

    char c = keyboardEventToAscii(ev);

    switch (c) {
        case '\n': {
            rl->line[rl->pos] = '\0';
        
            termPutChar(term, '\n', term->currentFg, term->currentBg);
        
            historyAdd(rl->line);
        
            return true;
        }

        case '\b': {
            if (ev->state.control) {
                while (rl->pos > 0 &&
                    rl->line[rl->pos - 1] == ' ') {
                    rl->pos--;
                    rl->line[rl->pos] = '\0';
                    putchar('\b');
                }

                while (rl->pos > 0 &&
                    rl->line[rl->pos - 1] != ' ') {
                    rl->pos--;
                    rl->line[rl->pos] = '\0';
                    putchar('\b');
                }
            } else if (rl->pos > 0) {
                rl->pos--;
                rl->line[rl->pos] = '\0';
                putchar('\b');
            }

            return false;
        }
    }
    
    if (c && rl->pos < sizeof(rl->line)-1) {
        rl->line[rl->pos++] = c;

        putchar(c);
        fflush(stdout);
    }

    return false;
}
