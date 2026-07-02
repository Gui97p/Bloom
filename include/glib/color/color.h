#pragma once

#define COLOR_BLACK      0x000000
#define COLOR_WHITE      0xFFFFFF
#define COLOR_RED        0xFF0000
#define COLOR_GREEN      0x00FF00
#define COLOR_BLUE       0x0000FF

#define COLOR_HOVER_AMOUNT  10
#define COLOR_ACTIVE_AMOUNT 15
#define COLOR_DISABLED_AMOUNT 40
#define COLOR_SELECTION_AMOUNT 25

#include <stdint.h>

typedef struct {
    uint32_t bg;
    uint32_t fg;
    uint32_t border;
    
    uint32_t accent;
    uint32_t accentHover;
    uint32_t accentPress;

    uint32_t disabled;
} colorPalette_t;

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t colorDarken(uint32_t color, uint8_t amount);
uint32_t colorLighten(uint32_t color, uint8_t amount);
