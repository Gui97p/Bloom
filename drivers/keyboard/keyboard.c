#include <drivers/keyboard/keyboard.h>
#include <sys/sys.h>

#define KEYBOARD_QUEUE_SIZE 64

typedef struct {
    bool lshift;
    bool rshift;
} keyboardState_t;

static keyboardState_t state;

static keyEvent_t queue[KEYBOARD_QUEUE_SIZE];

static int head = 0;
static int tail = 0;

static bool extended = false;

static void pushEvent(keyEvent_t event) {
    int next = (tail + 1) % KEYBOARD_QUEUE_SIZE;

    if (next == head) {
        return;
    }

    queue[tail] = event;
    tail = next;
}

void keyboardInit(void) {
    state.lshift = false;
    state.rshift = false;

    head = 0;
    tail = 0;
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
    
            default:
                break;
        }
    
    }
    
    if (key == KEY_NONE)
        return;

    pushEvent((keyEvent_t) {
        .key = key,
        .pressed = !released,
        .shift = state.lshift || state.rshift
    });
}

bool keyboardPopEvent(keyEvent_t* event) {
    if (head == tail)
        return false;

    *event = queue[head];

    head = (head + 1) % KEYBOARD_QUEUE_SIZE;

    return true;
}

char keyboardEventToAscii(keyEvent_t* ev) {
    if (ev->shift)
        return keyToAsciiUpper[ev->key];

    return keyToAscii[ev->key];
}

bool keyboardReadEvent(keyEvent_t* ev) {
    static uint8_t pending[64];
    static int pos = 0;
    static int size = 0;

    static bool keyState[256] = {0};
    static bool nextExtended = false;

    while (1) {
        if (pos >= size) {
            size = sys_read(FD_STDIN, pending, sizeof(pending));
            pos = 0;
            if (size <= 0)
                continue;
        }

        uint8_t scancode = pending[pos++];

        if (scancode == 0xE0) {
            nextExtended = true;
            keyboardFeedScancode(scancode);
            continue;
        }

        bool released = (scancode & 0x80) != 0;
        uint8_t base = scancode & 0x7F;

        if (nextExtended) {
            nextExtended = false;
        } else {
            if (!released && keyState[base])
                continue;
            if (released && !keyState[base])
                continue;
            keyState[base] = !released;
        }

        keyboardFeedScancode(scancode);

        if (keyboardPopEvent(ev)) {
            return true;
        }
    }
}
