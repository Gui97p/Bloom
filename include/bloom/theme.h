#pragma once
#include <stdint.h>

typedef struct {
    // [palette]
    uint32_t bg_deep;
    uint32_t bg_surface;
    uint32_t fg_primary;
    uint32_t fg_dim;
    uint32_t accent_purple;
    uint32_t accent_bright;
    uint32_t accent_teal;
    uint32_t accent_gold;
    uint32_t accent_pink;

    // [shell]
    uint8_t cursor_blink;

    // [statusbar]
    uint8_t statusbar_enabled;
    uint8_t show_uptime;
    uint8_t show_mem;
    uint8_t show_time;
} bloomTheme_t;

// Defaults lavanda
static const bloomTheme_t BLOOM_THEME_DEFAULT = {
    .bg_deep      = 0x0F0A1A,
    .bg_surface   = 0x13091F,
    .fg_primary   = 0xC5B3E6,
    .fg_dim       = 0x7A6899,
    .accent_purple= 0x9D7FD4,
    .accent_bright= 0xCC88FF,
    .accent_teal  = 0x80D4C8,
    .accent_gold  = 0xE8C47A,
    .accent_pink  = 0xE685B5,
    .cursor_blink       = 1,
    .statusbar_enabled  = 1,
    .show_uptime        = 1,
    .show_mem           = 1,
    .show_time          = 1,
};

bloomTheme_t themeLoad(const char* path);
void setupThemeFile();
