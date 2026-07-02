#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <glib/theme/ui.h>

typedef struct {
    uiTheme_t ui;

    uint32_t desktopBackground;
    bool taskbarEnabled;
} bloomTheme_t;

static const bloomTheme_t BLOOM_THEME_DEFAULT = {
    .ui = {
        .pallete = {
            .background      = 0x0F0A1A,
            .surface         = 0x13091F,
            .surfaceVariant  = 0x1A112A,

            .foreground      = 0xC5B3E6,
            .foregroundDim   = 0x7A6899,

            .border          = 0x6B5A88,
            .borderLight     = 0xA087D6,

            .success         = 0x80D4C8,
            .warning         = 0xE8C47A,
            .error           = 0xD45A7A,

            .primary         = 0x9D7FD4,
            .secondary       = 0xCC88FF,
            .tertiary        = 0xE685B5,
        },

        .defaultFont = &font8x16,
    },

    .desktopBackground = 0x0F0A1A,
    .taskbarEnabled = true,
};

extern bloomTheme_t bloomTheme;

bloomTheme_t themeLoad(const char* path);
void setupThemeFile();
