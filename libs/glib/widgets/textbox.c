#include <string.h>

#include <glib/gfx/rect.h>
#include <glib/gfx/line.h>

#include <glib/theme/ui.h>
#include <glib/containers/widget.h>

static inline void textBoxEnsureCursorVisible(textBox_t* textBox) {
    int visibleChars = (textBox->widget.width - 8) / textBox->font->width;

    if ((int)textBox->cursor < textBox->scrollX)
        textBox->scrollX = textBox->cursor;

    if ((int)textBox->cursor > textBox->scrollX + visibleChars)
        textBox->scrollX = textBox->cursor - visibleChars + 1;
    
    if ((int)textBox->length <= visibleChars) {
        textBox->scrollX = 0;
    } else {
        int maxScroll = textBox->length - visibleChars;
        if (textBox->scrollX < maxScroll)
            textBox->scrollX = maxScroll;
    }
}

static inline void textBoxInsert(textBox_t* textBox, char c) {
    if (textBox->length + 1 >= textBox->capacity)
        return;
    
    memmove(textBox->buffer + textBox->cursor + 1, textBox->buffer + textBox->cursor, textBox->length - textBox->cursor + 1);

    textBox->buffer[textBox->cursor] = c;

    textBox->cursor++;
    textBox->length++;

    textBoxEnsureCursorVisible(textBox);
}

static inline void textBoxBackspace(textBox_t* textBox) {
    if (textBox->cursor == 0)
        return;

    memmove(
        textBox->buffer + textBox->cursor - 1,
        textBox->buffer + textBox->cursor,
        textBox->length - textBox->cursor + 1
    );

    textBox->cursor--;
    textBox->length--;

    textBoxEnsureCursorVisible(textBox);
}

static inline void textBoxDelete(textBox_t* textBox) {
    if (textBox->cursor >= textBox->length)
        return;

    memmove(
        textBox->buffer + textBox->cursor,
        textBox->buffer + textBox->cursor + 1,
        textBox->length - textBox->cursor
    );

    textBox->length--;

    textBoxEnsureCursorVisible(textBox);
}

static void textBoxDraw(widget_t* widget, gfxSurface_t* surface) {
    textBox_t* textBox = (textBox_t*)widget;

    textBoxStyle_t* style = &textBox->style;

    font_t* font = textBox->font;
    if (!font)
        font = widget->container->theme->defaultFont;

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, style->bg);
    gfxDrawFrame(surface, widget->x, widget->y, widget->width, widget->height, &style->frame);

    int visibleChars = (widget->width - 8) / font->width;
    char backup = textBox->buffer[textBox->scrollX + visibleChars];

    if (textBox->scrollX + visibleChars < textBox->length)
        textBox->buffer[textBox->scrollX + visibleChars] = 0;

    gfxDrawString(surface, textBox->font, widget->x + 4, widget->y + 4, textBox->buffer + textBox->scrollX, style->fg);

    if (textBox->scrollX + visibleChars < textBox->length)
        textBox->buffer[textBox->scrollX + visibleChars] = backup;

    if (widget->focused && textBox->cursorVisible) {
        int cursorX = widget->x + 4 + gfxMeasureString(textBox->font, (textBox->cursor - textBox->scrollX));

        gfxDrawVLine(surface, cursorX, widget->y + 3, widget->y + textBox->font->height + 3, style->fg);
    }
}

static void textBoxEvent(widget_t* widget, event_t* ev) {
    textBox_t* textBox = (textBox_t*)widget;

    switch (ev->type) {
        case EVENT_KEY_DOWN: {
            switch (ev->key.key) {
                case KEY_BACKSPACE: {
                    textBoxBackspace(textBox);
                    break;
                }

                case KEY_DELETE: {
                    textBoxDelete(textBox);
                    break;
                }

                case KEY_HOME: {
                    textBox->cursor = 0;
                    break;
                }

                case KEY_END: {
                    textBox->cursor = textBox->length;
                    break;
                }

                case KEY_LEFT: {
                    if (textBox->cursor > 0)
                        textBox->cursor--;
                    break;
                }

                case KEY_RIGHT: {
                    if (textBox->cursor < textBox->length)
                        textBox->cursor++;
                    break;
                }
                
                default: {
                    char c = keyboardEventToAscii(&ev->key);

                    if (c > 32 && c < 126) {
                        textBoxInsert(textBox, c);
                    }

                    break;
                }
            }
            textBoxEnsureCursorVisible(textBox);

            break;
        }

        case EVENT_MOUSE_DOWN: {
            int pos = (ev->mouse.x - 4) / textBox->font->width;
        
            if (pos < 0) pos = 0;

            textBox->cursor = textBox->scrollX + pos;

            if (textBox->cursor > textBox->length)
                textBox->cursor = textBox->length;
            
            textBoxEnsureCursorVisible(textBox);

            break;
        }

        default:
            break;
    }
}

static void textBoxWidgetEvent(widget_t* widget, widgetEvent_t* ev) {
    textBox_t* textBox = (textBox_t*)widget;

    switch (ev->type) {
        case WIDGET_EVENT_FOCUS:
            textBox->cursorVisible = true;
            break;
        
        case WIDGET_EVENT_UNFOCUS: {
            textBox->cursorVisible = false;
            textBox->selectionStart = textBox->selectionEnd = textBox->cursor;
            break;
        }

        default:
            break;
    }
}

static void textBoxApplyTheme(widget_t* widget) {
    textBox_t* textBox = (textBox_t*)widget;
    textBoxStyle_t* theme = &widget->container->theme->textBox;
    textBox->style = *theme;

    WIDGET_APPLY_IF(textBox, fg, TEXTBOX_CUSTOM_FG, theme->fg);
    WIDGET_APPLY_IF(textBox, bg, TEXTBOX_CUSTOM_BG, theme->bg);
    WIDGET_APPLY_IF(textBox, selectionBg, TEXTBOX_CUSTOM_SELECTION_BG, theme->selectionBg);

    WIDGET_FRAME_APPLY_IF(textBox, border, TEXTBOX_CUSTOM_BORDER, theme->frame.border);
    WIDGET_FRAME_APPLY_IF(textBox, borderRadius, TEXTBOX_CUSTOM_BORDER_RADIUS, theme->frame.borderRadius);
    WIDGET_FRAME_APPLY_IF(textBox, borderSize,  TEXTBOX_CUSTOM_BORDER_SIZE, theme->frame.borderSize);
    WIDGET_FRAME_APPLY_IF(textBox, borderColor, TEXTBOX_CUSTOM_BORDER_COLOR, theme->frame.borderColor);
}

void textBoxInit(textBox_t* textBox, widgetContainer_t* container, int x, int y, int w, int h, char* buffer, size_t capacity) {
    widgetInit(&textBox->widget, x, y, w, h, WIDGET_TEXTBOX);

    textBox->widget.draw = textBoxDraw;
    textBox->widget.onEvent = textBoxEvent;
    textBox->widget.onWidgetEvent = textBoxWidgetEvent;
    textBox->widget.applyTheme = textBoxApplyTheme;
    
    textBox->customFields = TEXTBOX_CUSTOM_NONE;

    textBox->font = &font8x16;

    textBox->buffer = buffer;
    textBox->capacity = capacity;

    if (capacity > 0) {
        buffer[capacity - 1] = '\0';
        textBox->length = strlen(buffer);
        if (textBox->length >= capacity)
            textBox->length = capacity - 1;
    } else {
        textBox->length = 0;
    }

    textBox->cursor = textBox->length;
    textBox->cursorVisible = false;

    textBox->selecting = false;
    textBox->selectionStart = textBox->cursor;
    textBox->selectionEnd = textBox->cursor;

    textBox->scrollX = 0;
    
    widgetContainerAddWidget(container, &textBox->widget);
}