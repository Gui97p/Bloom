#pragma once

#include "keyboard.h"
#include "mouse.h"

typedef enum {
    EVENT_NONE,

    EVENT_KEY_DOWN,
    EVENT_KEY_UP,

    EVENT_MOUSE_MOVE,
    EVENT_MOUSE_DOWN,
    EVENT_MOUSE_UP
} eventType_t;

typedef struct {
    eventType_t type;

    union {
        keyEvent_t key;
        mouseEvent_t mouse;
    };
} event_t;

void eventPush(event_t ev);
bool eventPop(event_t* ev);
bool eventPoll(event_t* ev);
void eventPump();
