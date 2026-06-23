#include <glib/input/event.h>

int getchar() {
    event_t ev;
    
    while (1) {
        if (!eventPoll(&ev))
            continue;
        
        if (ev.type != EVENT_KEY_DOWN)
            continue;

        char c = keyboardEventToAscii(&ev.key);

        if (c)
            return c;
    }
}
