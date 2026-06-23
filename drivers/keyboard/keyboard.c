#include <stdio.h>
#include <glib/input/event.h>
#include <sys/read.h>
#include <sys/syscall.h>

static keyboardState_t state;

static bool extended = false;

void setupKeyboard(void) {
    state.lshift = false;
    state.rshift = false;
    state.control = false;
}

void keyboardFeedScancode(uint8_t scancode) {
    if (scancode == 0xE0) {
        extended = true;
        return;
    }

    bool released = false;

    if (scancode & 0x80) {
        released = true;
        scancode &= 0x7F;
    }

    keycode_t key;
    
    if (extended) {
        key = extendedScancodeMap[scancode];
        extended = false;
    } else {
        key = scancodeMap[scancode];
        switch (key) {
            case KEY_LSHIFT:
                state.lshift = !released;
                break;
    
            case KEY_RSHIFT:
                state.rshift = !released;
                break;
            
            case KEY_CTRL:
                state.control = !released;
                break;
    
            default:
                break;
        }
    
    }
    
    if (key == KEY_NONE)
        return;
    
    eventPush((event_t) {
        .type = !released ? EVENT_KEY_DOWN : EVENT_KEY_UP,
        
        .key = {
            .key = key,
            .pressed = !released,
            .state = (keyboardState_t) {
                .control = state.control,
                .lshift = state.lshift,
                .rshift = state.rshift,
                .shift = state.lshift || state.rshift
            }
        }
    });
}

char keyboardEventToAscii(keyEvent_t* ev) {
    if (ev->state.shift)
        return keyToAsciiUpper[ev->key];

    return keyToAscii[ev->key];
}
