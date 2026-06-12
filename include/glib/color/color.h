#pragma once

#define COLOR_BLACK      0x000000
#define COLOR_WHITE      0xFFFFFF
#define COLOR_RED        0xFF0000
#define COLOR_GREEN      0x00FF00
#define COLOR_BLUE       0x0000FF

#include <stdint.h>

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);
uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
