#include <stdio.h>

#include <glib/input/event.h>
#include <glib/input/keyboard.h>
#include <glib/input/mouse.h>

#include <bloom/debug.h>

#define EVENT_QUEUE_SIZE 64

static event_t queue[EVENT_QUEUE_SIZE];
static mouseState_t lastMouse;
static bool mouseInitialized = false;

static int head = 0;
static int tail = 0;

void eventPush(event_t ev) {
    int next = (tail + 1) % EVENT_QUEUE_SIZE;

    if (next == head) {
        return;
    }

    queue[tail] = ev;
    tail = next;
}

bool eventPop(event_t* ev) {
    if (head == tail)
        return false;

    *ev = queue[head];

    head = (head + 1) % EVENT_QUEUE_SIZE;

    return true;
}

void eventPump() {
    int c = fgetc(stdin);
    
    if (c != EOF) {
        uint8_t scancode = (uint8_t)c;
        keyboardFeedScancode(scancode);
    }

    mouseState_t current;

    if (fread(&current, sizeof(current), 1, mouse) > 0) {
        if (!mouseInitialized) {
            lastMouse = current;
            mouseInitialized = true;
        } else {
            if (current.x != lastMouse.x || current.y != lastMouse.y) {
                eventPush((event_t) {
                    .type = EVENT_MOUSE_MOVE,
                    .mouse = (mouseEvent_t) {
                        .x = current.x,
                        .y = current.y,
                        .dx = current.x - lastMouse.x,
                        .dy = current.y - lastMouse.y,
                        
                        .button = MOUSE_BUTTON_NONE
                    }
                });
            }
            
            if (current.left != lastMouse.left) {
                eventPush((event_t){
                    .type = current.left
                        ? EVENT_MOUSE_DOWN
                        : EVENT_MOUSE_UP,

                    .mouse = (mouseEvent_t) {
                        .x = current.x,
                        .y = current.y,
                        .dx = current.x - lastMouse.x,
                        .dy = current.y - lastMouse.y,
                        
                        .button = MOUSE_BUTTON_LEFT
                    }
                });
            }

            if (current.right != lastMouse.right) {
                eventPush((event_t){
                    .type = current.right
                        ? EVENT_MOUSE_DOWN
                        : EVENT_MOUSE_UP,

                    .mouse = (mouseEvent_t) {
                        .x = current.x,
                        .y = current.y,
                        .dx = current.x - lastMouse.x,
                        .dy = current.y - lastMouse.y,
                        
                        .button = MOUSE_BUTTON_RIGHT
                    }
                });
            }

            if (current.middle != lastMouse.middle) {
                eventPush((event_t){
                    .type = current.middle
                        ? EVENT_MOUSE_DOWN
                        : EVENT_MOUSE_UP,

                    .mouse = (mouseEvent_t) {
                        .x = current.x,
                        .y = current.y,
                        .dx = current.x - lastMouse.x,
                        .dy = current.y - lastMouse.y,
                        
                        .button = MOUSE_BUTTON_MIDDLE
                    }
                });
            }

            lastMouse = current;
        }
    }
}

bool eventPoll(event_t* ev) {
    return eventPop(ev);
}
