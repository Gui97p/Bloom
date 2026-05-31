#ifndef KEYMAP_H
#define KEYMAP_H

typedef enum {
    KEY_NONE = 0,

    KEY_ESC,
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5,
    KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,

    KEY_MINUS,
    KEY_EQUAL,
    KEY_BACKSPACE,
    KEY_TAB,

    KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,
    KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,

    KEY_LBRACKET,
    KEY_RBRACKET,
    KEY_ENTER,

    KEY_A, KEY_S, KEY_D, KEY_F, KEY_G,
    KEY_H, KEY_J, KEY_K, KEY_L,

    KEY_SEMICOLON,
    KEY_APOSTROPHE,
    KEY_GRAVE,

    KEY_LSHIFT,

    KEY_BACKSLASH,

    KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,
    KEY_N, KEY_M,

    KEY_COMMA,
    KEY_DOT,
    KEY_SLASH,

    KEY_RSHIFT,

    KEY_SPACE,

    KEY_MAX
} keycode_t;

static const keycode_t scancodeMap[128] = {
    [0x01] = KEY_ESC,

    [0x02] = KEY_1,
    [0x03] = KEY_2,
    [0x04] = KEY_3,
    [0x05] = KEY_4,
    [0x06] = KEY_5,
    [0x07] = KEY_6,
    [0x08] = KEY_7,
    [0x09] = KEY_8,
    [0x0A] = KEY_9,
    [0x0B] = KEY_0,

    [0x0C] = KEY_MINUS,
    [0x0D] = KEY_EQUAL,
    [0x0E] = KEY_BACKSPACE,
    [0x0F] = KEY_TAB,

    [0x10] = KEY_Q,
    [0x11] = KEY_W,
    [0x12] = KEY_E,
    [0x13] = KEY_R,
    [0x14] = KEY_T,
    [0x15] = KEY_Y,
    [0x16] = KEY_U,
    [0x17] = KEY_I,
    [0x18] = KEY_O,
    [0x19] = KEY_P,

    [0x1A] = KEY_LBRACKET,
    [0x1B] = KEY_RBRACKET,

    [0x1C] = KEY_ENTER,

    [0x1E] = KEY_A,
    [0x1F] = KEY_S,
    [0x20] = KEY_D,
    [0x21] = KEY_F,
    [0x22] = KEY_G,
    [0x23] = KEY_H,
    [0x24] = KEY_J,
    [0x25] = KEY_K,
    [0x26] = KEY_L,

    [0x27] = KEY_SEMICOLON,
    [0x28] = KEY_APOSTROPHE,
    [0x29] = KEY_GRAVE,

    [0x2A] = KEY_LSHIFT,

    [0x2B] = KEY_BACKSLASH,

    [0x2C] = KEY_Z,
    [0x2D] = KEY_X,
    [0x2E] = KEY_C,
    [0x2F] = KEY_V,
    [0x30] = KEY_B,
    [0x31] = KEY_N,
    [0x32] = KEY_M,

    [0x33] = KEY_COMMA,
    [0x34] = KEY_DOT,
    [0x35] = KEY_SLASH,

    [0x36] = KEY_RSHIFT,

    [0x39] = KEY_SPACE,
};

static const char keyToAscii[KEY_MAX] = {
    [KEY_1] = '1',
    [KEY_2] = '2',
    [KEY_3] = '3',
    [KEY_4] = '4',
    [KEY_5] = '5',
    [KEY_6] = '6',
    [KEY_7] = '7',
    [KEY_8] = '8',
    [KEY_9] = '9',
    [KEY_0] = '0',

    [KEY_MINUS] = '-',
    [KEY_EQUAL] = '=',

    [KEY_Q] = 'q',
    [KEY_W] = 'w',
    [KEY_E] = 'e',
    [KEY_R] = 'r',
    [KEY_T] = 't',
    [KEY_Y] = 'y',
    [KEY_U] = 'u',
    [KEY_I] = 'i',
    [KEY_O] = 'o',
    [KEY_P] = 'p',

    [KEY_A] = 'a',
    [KEY_S] = 's',
    [KEY_D] = 'd',
    [KEY_F] = 'f',
    [KEY_G] = 'g',
    [KEY_H] = 'h',
    [KEY_J] = 'j',
    [KEY_K] = 'k',
    [KEY_L] = 'l',

    [KEY_ENTER] = '\n',

    [KEY_Z] = 'z',
    [KEY_X] = 'x',
    [KEY_C] = 'c',
    [KEY_V] = 'v',
    [KEY_B] = 'b',
    [KEY_N] = 'n',
    [KEY_M] = 'm',

    [KEY_SPACE] = ' ',

    [KEY_COMMA] = ',',
    [KEY_DOT] = '.',
    [KEY_SLASH] = ';',

    [KEY_SEMICOLON] = 'c',
    [KEY_APOSTROPHE] = '~',
    [KEY_GRAVE] = '\'',

    [KEY_LBRACKET] = '[',
    [KEY_RBRACKET] = ']',

    [KEY_BACKSLASH] = '\\',
};

static const char keyToAsciiUpper[KEY_MAX] = {
    [KEY_1] = '!',
    [KEY_2] = '@',
    [KEY_3] = '#',
    [KEY_4] = '$',
    [KEY_5] = '%',
    [KEY_6] = ' ',
    [KEY_7] = '&',
    [KEY_8] = '*',
    [KEY_9] = '(',
    [KEY_0] = ')',

    [KEY_MINUS] = '_',
    [KEY_EQUAL] = '+',

    [KEY_Q] = 'Q',
    [KEY_W] = 'W',
    [KEY_E] = 'E',
    [KEY_R] = 'R',
    [KEY_T] = 'T',
    [KEY_Y] = 'Y',
    [KEY_U] = 'U',
    [KEY_I] = 'I',
    [KEY_O] = 'O',
    [KEY_P] = 'P',

    [KEY_A] = 'A',
    [KEY_S] = 'S',
    [KEY_D] = 'D',
    [KEY_F] = 'F',
    [KEY_G] = 'G',
    [KEY_H] = 'H',
    [KEY_J] = 'J',
    [KEY_K] = 'K',
    [KEY_L] = 'L',

    [KEY_ENTER] = '\n',

    [KEY_Z] = 'Z',
    [KEY_X] = 'X',
    [KEY_C] = 'C',
    [KEY_V] = 'V',
    [KEY_B] = 'B',
    [KEY_N] = 'N',
    [KEY_M] = 'M',

    [KEY_COMMA] = '<',
    [KEY_DOT] = '>',
    [KEY_SLASH] = ':',

    [KEY_SEMICOLON] = 'C',
    [KEY_APOSTROPHE] = '^',
    [KEY_GRAVE] = '"',

    [KEY_LBRACKET] = '{',
    [KEY_RBRACKET] = '}',

    [KEY_BACKSLASH] = '|',

    [KEY_SPACE] = ' ',
};

#endif