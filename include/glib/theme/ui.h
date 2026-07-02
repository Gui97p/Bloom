#pragma once

#include <glib/fonts/font.h>
#include <glib/widgets/widgets.h>

#include "pallete.h"

typedef struct uiTheme {
    uiPallete_t pallete;
    font_t* defaultFont;

    buttonStyle_t button;
    checkBoxStyle_t checkBox;
    labelStyle_t label;
    panelStyle_t panel;
    progressBarStyle_t progressBar;
    sliderStyle_t slider;
    textBoxStyle_t textBox;
} uiTheme_t;
