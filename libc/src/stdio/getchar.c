#include <sys/sys.h>
#include <drivers/keyboard/keyboard.h>

int getchar() {
    unsigned char sc;

    while (1) {
        if (sys_read(FD_STDIN, &sc, 1) != 1)
            continue;

        keyboardFeedScancode(sc);

        keyEvent_t ev;

        while (keyboardPopEvent(&ev)) {
            if (!ev.pressed)
                continue;

            char c = keyboardEventToAscii(&ev);

            if (c)
                return c;
        }
    }
}
