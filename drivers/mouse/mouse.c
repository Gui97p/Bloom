#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib/input/mouse.h>
#include <bloom/debug.h>

FILE* mouse;

int setupMouse() {
    mouse = fopen("/dev/mouse", "r");

    if (!mouse) {
        DPRINTF("[BLOOM] mouse: failed to open\n");
        return -1;
    }

    DPRINTF("[BLOOM] mouse: opened\n");

    return 0;
}
