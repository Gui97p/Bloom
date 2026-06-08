#include <drivers/keyboard/keyboard.h>

int getchar() {
    keyEvent_t ev;
    
    while (1) {
        if (!keyboardReadEvent(&ev))
            continue;
        
        if (!ev.pressed)
            continue;

        char c = keyboardEventToAscii(&ev);

        if (c)
            return c;
    }
}
