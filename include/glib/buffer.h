#pragma once

#include <stdint.h>

#define FRAMEBUFFER_ADDR 0x7000000000
#define FRAMEBUFFER_INFO 0x7100000000
#define BACKBUFFER_ADDR 0x7200000000

typedef struct {
    // uint64_t address;

    uint64_t width;
    uint64_t height;
    uint64_t pitch;
} FramebufferInfo;

void setupFramebuffer();

extern uint32_t* fb;
extern uint32_t* bb;
extern FramebufferInfo* fb_info;
