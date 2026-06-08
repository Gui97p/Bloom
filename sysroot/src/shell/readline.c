#include <stdio.h>
#include <string.h>
#include <drivers/keyboard/keyboard.h>

#define HISTORY_SIZE 32
#define MAX_CMD_LEN 256

static char historyBuffer[HISTORY_SIZE][MAX_CMD_LEN];
static int historyCount = 0;
static int historyPos = -1;

void historyAdd(const char* cmd) {
    if (cmd[0] == '\0')
        return;
    
        if (historyCount > 0 && strcmp(historyBuffer[(historyCount-1) % HISTORY_SIZE], cmd) == 0)
            return;
        
        strncpy(historyBuffer[historyCount % HISTORY_SIZE], cmd, MAX_CMD_LEN-1);
        historyBuffer[historyCount % HISTORY_SIZE][MAX_CMD_LEN-1] = '\0';
        historyCount++;
}

static void clearLine(int len) {
    for (int i = 0; i < len; i ++) {
        putchar('\b');
        putchar(' ');
        putchar('\b');
    }
}

char* readline(char* buf, int size) {
    int i = 0;

    keyEvent_t ev;

    char tmp[MAX_CMD_LEN] = {0};
    historyPos = -1;

    while (1) {
        if (!keyboardReadEvent(&ev))
            continue;
        
        if (!ev.pressed)
            continue;
        
        switch (ev.key) {
            case KEY_UP:
                int next = historyPos + 1;
                int maxPos = historyCount > HISTORY_SIZE ? HISTORY_SIZE : historyCount;
                if (next >= maxPos)
                    continue;
                
                if (historyPos == -1) {
                    buf[i] = '\0';
                    strcpy(tmp, buf);
                }

                historyPos = next;
                int idx = (historyCount - 1 - historyPos + HISTORY_SIZE) % HISTORY_SIZE;

                clearLine(i);
                strncpy(buf, historyBuffer[idx], size - 1);
                buf[size - 1] = '\0';
                i = strlen(buf);
                printf("%s", buf);

                fflush(stdout);
                continue;
            
            case KEY_DOWN: {
                if (historyPos == -1)
                    continue;

                historyPos--;

                clearLine(i);

                if (historyPos == -1) {
                    strncpy(buf, tmp, size - 1);
                } else {
                    int idx = (historyCount - 1 - historyPos + HISTORY_SIZE) % HISTORY_SIZE;
                    strncpy(buf, historyBuffer[idx], size - 1);
                }

                buf[size - 1] = '\0';
                i = strlen(buf);
                printf("%s", buf);
                fflush(stdout);
                continue;
            }

            default:
                break;
        }

        char c = keyboardEventToAscii(&ev);

        if (c) {
            if (c == '\n') {
                putchar('\n');
                break;
            }

            if (c == '\b') {
                if (i > 0) {
                    i--;

                    putchar('\b');
                    putchar(' ');
                    putchar('\b');
                }

                fflush(stdout);
                continue;
            }

            if (i < size - 1) {
                buf[i++] = c;
                putchar(c);
                historyPos = -1;
            }
        }

        fflush(stdout);
    }

    buf[i] = '\0';
    historyAdd(buf);
    return buf;
}