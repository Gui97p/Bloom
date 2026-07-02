#pragma once

#include <stdint.h>

typedef struct {
    uint32_t background;
    uint32_t surface;
    uint32_t surfaceVariant;

    uint32_t foreground;
    uint32_t foregroundDim;

    uint32_t selection;

    uint32_t border;
    uint32_t borderLight;

    uint32_t success;
    uint32_t warning;
    uint32_t error;

    uint32_t primary;
    uint32_t secondary;
    uint32_t tertiary;
} uiPallete_t;
