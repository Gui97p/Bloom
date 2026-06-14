#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bin/terminal/terminal.h>
#include <glib/gfx/rect.h>
#include <bloom/theme.h>

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

bloomTheme_t themeLoad(const char* path) {
    bloomTheme_t theme = BLOOM_THEME_DEFAULT;

    FILE* f = fopen(path, "r");
    if (!f) return theme;

    char buf[1024];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);

    if (n == 0) return theme;
    buf[n] = '\0';

    char *line = buf;
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

                if      (!strcmp(key, "bg_deep"))       theme.bg_deep       = parseHexColor(val);
                else if (!strcmp(key, "bg_surface"))     theme.bg_surface    = parseHexColor(val);
                else if (!strcmp(key, "fg_primary"))     theme.fg_primary    = parseHexColor(val);
                else if (!strcmp(key, "fg_dim"))         theme.fg_dim        = parseHexColor(val);
                else if (!strcmp(key, "accent_purple"))  theme.accent_purple = parseHexColor(val);
                else if (!strcmp(key, "accent_bright"))  theme.accent_bright = parseHexColor(val);
                else if (!strcmp(key, "accent_teal"))    theme.accent_teal   = parseHexColor(val);
                else if (!strcmp(key, "accent_gold"))    theme.accent_gold   = parseHexColor(val);
                else if (!strcmp(key, "accent_pink"))    theme.accent_pink   = parseHexColor(val);
                else if (!strcmp(key, "cursor_blink"))   theme.cursor_blink  = parseBool(val);
                else if (!strcmp(key, "enabled"))        theme.statusbar_enabled = parseBool(val);
                else if (!strcmp(key, "show_uptime"))    theme.show_uptime   = parseBool(val);
                else if (!strcmp(key, "show_mem"))       theme.show_mem      = parseBool(val);
                else if (!strcmp(key, "show_time"))      theme.show_time     = parseBool(val);
            }
        }
        line = next;
    }

    return theme;
}

void termApplyTheme(terminal_t* term, const bloomTheme_t* theme) {
    termSetColor(term, theme->fg_primary, theme->bg_deep);

    gfxBeginFrame(term->gfx);
    fillRect(term->gfx, 0, 0, term->gfx->width, term->gfx->height, theme->bg_deep);
    gfxEndFrame(term->gfx);

    memset(term->previous, 0xFF, term->rows * term->cols * sizeof(termCell_t));
}

void setupThemeFile() {
    FILE* f = fopen("theme.conf", "w+");

    char* content = "[palette]\nbg_deep       = #0f0a1a\nbg_surface    = #13091f\nfg_primary    = #c5b3e6\nfg_dim        = #7a6899\naccent_purple = #9d7fd4\naccent_bright = #cc88ff\naccent_teal   = #80d4c8\naccent_gold   = #e8c47a\naccent_pink   = #e685b5\n\n[shell]\nprompt_style  = user@host:path$\ncursor_style  = block\ncursor_blink  = true\n\n[statusbar]\nenabled       = true\nshow_uptime   = true\nshow_mem      = true\nshow_time     = true";

    fwrite(content, 1, strlen(content), f);

    fclose(f);
}
