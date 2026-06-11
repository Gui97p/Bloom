#include <glib/buffer.h>

uint32_t* fb = (uint32_t*)FRAMEBUFFER_ADDR;
uint32_t* bb = (uint32_t*)BACKBUFFER_ADDR;
FramebufferInfo* fb_info = (FramebufferInfo*)FRAMEBUFFER_INFO;
