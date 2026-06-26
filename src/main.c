#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <bin/console/console.h>
#include <bin/compositor/compositor.h>

#include <bloom/theme.h>
#include <bloom/debug.h>

#include <glib/gfx/context.h>
#include <glib/gfx/line.h>
#include <glib/gfx/blit.h>
#include <glib/gfx/rect.h>
#include <glib/buffer.h>
#include <glib/fonts/font.h>
#include <glib/input/keyboard.h>
#include <glib/input/mouse.h>
#include <glib/widgets/label.h>
#include <glib/widgets/button.h>
#include <glib/widgets/panel.h>

typedef struct {
    int count;
    char text[32];
} CounterData;

void onButtonClick(button_t* button, void* userdata) {
    CounterData* data = userdata;

    data->count++;
    sprintf(data->text, "Count: %d", data->count);
}

int main() {
    setupKeyboard();
    setupMouse();
    setupFramebuffer();
    setupThemeFile();

    gfxContext_t ctx;
    gfxInit(&ctx, fb, fb_info.width, fb_info.height, fb_info.pitch);

    gfxWindow_t window;
    gfxCreateWindow(&window, 300, 300, "Tela 1");

    CounterData counter;
    counter.count = 0;
    sprintf(counter.text, "Count: %d", counter.count);

    panel_t panel;
    panelInit(&panel, 0, 0, 300, 100, 0x555555);

    label_t label;
    labelInit(&label, 50, 0, 76, 28, &font8x16, counter.text);

    button_t button;
    buttonInit(&button, 50, 50, 100, 30, &font8x16, "Click me");
    button.onClick = onButtonClick;
    button.widget.userData = &counter;

    windowAddWidget(&window, &panel.widget);
    windowAddWidget(&window, &label.widget);
    windowAddWidget(&window, &button.widget);
    
    while (1) {
        compositorLoop(&ctx, &window);
    }
}
