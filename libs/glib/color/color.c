#include <stdint.h>

static inline uint8_t clamp(int x) {
    if (x < 0) return 0;
    if (x > 255) return 255;
    return x;
}

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) |
           ((uint32_t)g << 8)  |
           (uint32_t)b;
}

uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return ((uint32_t)a << 24) |
           ((uint32_t)r << 16) |
           ((uint32_t)g << 8)  |
           (uint32_t)b;
}

uint32_t colorDarken(uint32_t color, uint8_t amount) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r -= r * amount / 255;
    g -= g * amount / 255;
    b -= b * amount / 255;

    return rgb(r, g, b);
}

uint32_t colorLighten(uint32_t color, uint8_t amount) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r += (255 - r) * amount / 255;
    g += (255 - g) * amount / 255;
    b += (255 - b) * amount / 255;

    return rgb(r, g, b);
}
