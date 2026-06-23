#pragma once

#include <stdint.h>
#include <stdio.h>

typedef enum {
    MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE
} mouseButton_t;

typedef struct {
    int32_t x;
    int32_t y;

    int32_t dx;
    int32_t dy;

    mouseButton_t button;
} mouseEvent_t;

typedef struct {
    int32_t x;
    int32_t y;

    uint8_t left;
    uint8_t right;
    uint8_t middle;
} mouseState_t;

extern FILE* mouse;
int setupMouse();
