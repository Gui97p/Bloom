#include <string.h>

#include <glib/gfx/rect.h>
#include <glib/gfx/line.h>

#include <glib/widgets/textbox.h>
#include <glib/containers/widget.h>

static inline void textBoxEnsureCursorVisible(textBox_t* tb) {
    int visibleChars = (tb->widget.width - 8) / tb->font->width;

    if ((int)tb->cursor < tb->scrollX)
        tb->scrollX = tb->cursor;

    if ((int)tb->cursor > tb->scrollX + visibleChars)
        tb->scrollX = tb->cursor - visibleChars + 1;
    
    if ((int)tb->length <= visibleChars) {
        tb->scrollX = 0;
    } else {
        int maxScroll = tb->length - visibleChars;
        if (tb->scrollX < maxScroll)
            tb->scrollX = maxScroll;
    }
}

static inline void textBoxInsert(textBox_t* tb, char c) {
    if (tb->length + 1 >= tb->capacity)
        return;
    
    memmove(tb->buffer + tb->cursor + 1, tb->buffer + tb->cursor, tb->length - tb->cursor + 1);

    tb->buffer[tb->cursor] = c;

    tb->cursor++;
    tb->length++;

    textBoxEnsureCursorVisible(tb);
}

static inline void textBoxBackspace(textBox_t* tb) {
    if (tb->cursor == 0)
        return;

    memmove(
        tb->buffer + tb->cursor - 1,
        tb->buffer + tb->cursor,
        tb->length - tb->cursor + 1
    );

    tb->cursor--;
    tb->length--;

    textBoxEnsureCursorVisible(tb);
}

static inline void textBoxDelete(textBox_t* tb) {
    if (tb->cursor >= tb->length)
        return;

    memmove(
        tb->buffer + tb->cursor,
        tb->buffer + tb->cursor + 1,
        tb->length - tb->cursor
    );

    tb->length--;

    textBoxEnsureCursorVisible(tb);
}

static void textBoxDraw(widget_t* widget, gfxSurface_t* surface) {
    textBox_t* tb = (textBox_t*)widget;

    gfxFillRect(surface, widget->x, widget->y, widget->width, widget->height, tb->bg);
    gfxDrawRect(surface, widget->x, widget->y, widget->width, widget->height, widget->focused ? 0x4A90E2 : 0x808080);

    int visibleChars = (widget->width - 8) / tb->font->width;
    char backup = tb->buffer[tb->scrollX + visibleChars];

    if (tb->scrollX + visibleChars < tb->length)
        tb->buffer[tb->scrollX + visibleChars] = 0;

    gfxDrawString(surface, tb->font, widget->x + 4, widget->y + 4, tb->buffer + tb->scrollX, tb->fg);

    if (tb->scrollX + visibleChars < tb->length)
        tb->buffer[tb->scrollX + visibleChars] = backup;

    if (widget->focused && tb->cursorVisible) {
        int cursorX = widget->x + 4 + gfxMeasureString(tb->font, (tb->cursor - tb->scrollX));

        gfxDrawVLine(surface, cursorX, widget->y + 3, widget->y + tb->font->height + 3, tb->fg);
    }
}

static void textBoxEvent(widget_t* widget, event_t* ev) {
    textBox_t* tb = (textBox_t*)widget;

    switch (ev->type) {
        case EVENT_KEY_DOWN: {
            switch (ev->key.key) {
                case KEY_BACKSPACE: {
                    textBoxBackspace(tb);
                    break;
                }

                case KEY_DELETE: {
                    textBoxDelete(tb);
                    break;
                }

                case KEY_HOME: {
                    tb->cursor = 0;
                    break;
                }

                case KEY_END: {
                    tb->cursor = tb->length;
                    break;
                }

                case KEY_LEFT: {
                    if (tb->cursor > 0)
                        tb->cursor--;
                    break;
                }

                case KEY_RIGHT: {
                    if (tb->cursor < tb->length)
                        tb->cursor++;
                    break;
                }
                
                default: {
                    char c = keyboardEventToAscii(&ev->key);

                    if (c > 32 && c < 126) {
                        textBoxInsert(tb, c);
                    }

                    break;
                }
            }
            textBoxEnsureCursorVisible(tb);

            break;
        }

        case EVENT_MOUSE_DOWN: {
            int pos = (ev->mouse.x - 4) / tb->font->width;
        
            if (pos < 0) pos = 0;

            tb->cursor = tb->scrollX + pos;

            if (tb->cursor > tb->length)
                tb->cursor = tb->length;
            
            textBoxEnsureCursorVisible(tb);

            break;
        }

        default:
            break;
    }
}

static void textBoxWidgetEvent(widget_t* widget, widgetEvent_t* ev) {
    textBox_t* tb = (textBox_t*)widget;

    switch (ev->type) {
        case WIDGET_EVENT_FOCUS:
            tb->cursorVisible = true;
            break;
        
        case WIDGET_EVENT_UNFOCUS: {
            tb->cursorVisible = false;
            tb->selectionStart = tb->selectionEnd = tb->cursor;
            break;
        }

        default:
            break;
    }
}

void textBoxInit(textBox_t* textBox, int x, int y, int w, int h, char* buffer, size_t capacity) {
    widgetInit(&textBox->widget, x, y, w, h, WIDGET_TEXTBOX);

    textBox->widget.draw = textBoxDraw;
    textBox->widget.onEvent = textBoxEvent;
    textBox->widget.onWidgetEvent = textBoxWidgetEvent;

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

    textBox->fg = 0xFFFFFF;
    textBox->bg = 0x404040;
}