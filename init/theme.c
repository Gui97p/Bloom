#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib/gfx/rect.h>
#include <glib/color/color.h>
#include <bloom/theme.h>

bloomTheme_t bloomTheme;

static uint32_t parseHexColor(const char* str) {
    while (*str == ' ' || *str == '\t') str++;
    if (*str == '#') str++;
    return (uint32_t)strtoul(str, NULL, 16);
}

static int parseBool(const char* str) {
    while (*str == ' ' || *str == '\t') str++;
    return strncmp(str, "true", 4) == 0 ? 1 : 0;
}

static char* trim(char* s) {
    while (*s == ' ' || *s == '\t') s++;
    char* end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n'))
        *end-- = '\0';
    return s;
}

void uiThemeBuild(uiTheme_t* theme) {
    theme->button = (buttonStyle_t){
        .fg = theme->pallete.foreground,
        
        .bg = theme->pallete.primary,
        .bgHover = colorLighten(theme->pallete.primary, COLOR_HOVER_AMOUNT),
        .bgPress = colorDarken(theme->pallete.primary, COLOR_ACTIVE_AMOUNT),
        
        .frame = {
            .border = true,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
    };

    theme->label = (labelStyle_t){
        .fg = theme->pallete.foreground,
        .bg = theme->pallete.surface,

        .frame = {
            .border = false,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
        
    };

    theme->panel = (panelStyle_t){
        .bg = theme->pallete.surface,
        
        .frame = {
            .border = true,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
    };

    theme->textBox = (textBoxStyle_t){
        .fg = theme->pallete.foreground,
        .bg = theme->pallete.surfaceVariant,
        
        .cursorColor = theme->pallete.primary,
        .selectionBg = colorLighten(theme->pallete.primary, COLOR_SELECTION_AMOUNT),
        
        .frame = {
            .border = true,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
    };

    theme->checkBox = (checkBoxStyle_t){
        .bg = theme->pallete.surface,
        .bgHover = colorLighten(theme->pallete.surface, COLOR_HOVER_AMOUNT),
        .bgActive = theme->pallete.primary,
        .bgHoverActive = colorLighten(theme->pallete.primary, COLOR_HOVER_AMOUNT),
        
        .frame = {
            .border = true,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
    };

    theme->progressBar = (progressBarStyle_t){
        .fg = theme->pallete.primary,
        .bg = theme->pallete.surface,

        .frame = {
            .border = true,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
    };

    theme->slider = (sliderStyle_t){
        .fg = theme->pallete.surfaceVariant,
        .bg = theme->pallete.surface,
        .knob = theme->pallete.primary,

        .frame = {
            .border = true,
            .borderSize = 1,
            .borderColor = theme->pallete.border,
            .borderRadius = 0,
        }
    };
}

bloomTheme_t themeLoad(const char* path) {
    bloomTheme_t theme = BLOOM_THEME_DEFAULT;

    FILE* f = fopen(path, "r");
    if (!f) {
        uiThemeBuild(&theme.ui);
        return theme;
    }

    char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);

    if (n == 0) {
        uiThemeBuild(&theme.ui);
        return theme;
    }

    buf[n] = '\0';

    char* line = buf;
    while (line && *line) {
        char* next = strchr(line, '\n');
        if (next) *next++ = '\0';

        char* s = trim(line);

        if (*s && *s != '#' && *s != '[') {
            char* eq = strchr(s, '=');

            if (eq) {
                *eq = '\0';

                char* key = trim(s);
                char* val = trim(eq + 1);

                if      (!strcmp(key, "background"))      theme.ui.pallete.background      = parseHexColor(val);
                else if (!strcmp(key, "surface"))         theme.ui.pallete.surface         = parseHexColor(val);
                else if (!strcmp(key, "surfaceVariant"))  theme.ui.pallete.surfaceVariant  = parseHexColor(val);

                else if (!strcmp(key, "foreground"))      theme.ui.pallete.foreground      = parseHexColor(val);
                else if (!strcmp(key, "foregroundDim"))   theme.ui.pallete.foregroundDim   = parseHexColor(val);

                else if (!strcmp(key, "border"))          theme.ui.pallete.border          = parseHexColor(val);
                else if (!strcmp(key, "borderLight"))     theme.ui.pallete.borderLight     = parseHexColor(val);

                else if (!strcmp(key, "primary"))         theme.ui.pallete.primary         = parseHexColor(val);
                else if (!strcmp(key, "secondary"))       theme.ui.pallete.secondary       = parseHexColor(val);
                else if (!strcmp(key, "tertiary"))        theme.ui.pallete.tertiary        = parseHexColor(val);

                else if (!strcmp(key, "success"))         theme.ui.pallete.success         = parseHexColor(val);
                else if (!strcmp(key, "warning"))         theme.ui.pallete.warning         = parseHexColor(val);
                else if (!strcmp(key, "error"))           theme.ui.pallete.error           = parseHexColor(val);

                else if (!strcmp(key, "desktopBackground")) theme.desktopBackground = parseHexColor(val);
                else if (!strcmp(key, "taskbarEnabled"))    theme.taskbarEnabled = parseBool(val);
            }
        }

        line = next;
    }

    uiThemeBuild(&theme.ui);

    return theme;
}

void setupThemeFile() {
    FILE* f = fopen("/theme.conf", "w+");
    if (!f)
        return;

    const char* content =
        "[palette]\n"
        "background       = #0F0A1A\n"
        "surface          = #13091F\n"
        "surfaceVariant   = #1A112A\n"
        "\n"
        "foreground       = #C5B3E6\n"
        "foregroundDim    = #7A6899\n"
        "\n"
        "border           = #6B5A88\n"
        "borderLight      = #A087D6\n"
        "\n"
        "primary          = #9D7FD4\n"
        "secondary        = #CC88FF\n"
        "tertiary         = #E685B5\n"
        "\n"
        "success          = #80D4C8\n"
        "warning          = #E8C47A\n"
        "error            = #D45A7A\n"
        "\n"
        "[desktop]\n"
        "desktopBackground = #0F0A1A\n"
        "taskbarEnabled    = true\n";

    fwrite(content, 1, strlen(content), f);
    fclose(f);
}
