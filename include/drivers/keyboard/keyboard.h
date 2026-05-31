#pragma once

#include <drivers/keyboard/keymap.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    keycode_t key;
    bool pressed;
    bool shift;
} keyEvent_t;

void keyboardInit(void);

void keyboardFeedScancode(uint8_t scancode);

bool keyboardPopEvent(keyEvent_t* event);

char keyboardEventToAscii(keyEvent_t* ev);
