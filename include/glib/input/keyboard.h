#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "keymap.h"

typedef struct {
    bool lshift;
    bool rshift;
    bool shift;
    bool control;
} keyboardState_t;

typedef struct {
    keycode_t key;
    bool pressed;
    keyboardState_t state;
} keyEvent_t;

void setupKeyboard(void);
void keyboardFeedScancode(uint8_t scancode);
char keyboardEventToAscii(keyEvent_t* ev);
