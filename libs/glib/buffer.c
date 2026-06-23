#include <glib/buffer.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

uint32_t* fb = (uint32_t*)FRAMEBUFFER_ADDR;
uint32_t* bb = (uint32_t*)BACKBUFFER_ADDR;
FramebufferFile fb_info;

void setupFramebuffer() {
    int fb_fd = open("/sys/fb0", O_RDWR);
    read(fb_fd, &fb_info, sizeof(FramebufferFile));
}
