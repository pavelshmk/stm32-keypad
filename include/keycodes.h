#pragma once

#include "keycodes_hash.h"

typedef enum {
    KC_NO = 0x0000,
    KC_ROLL_OVER = 0x0001,
    KC_POST_FAIL = 0x0002,
    KC_UNDEFINED = 0x0003,
    KC_A = 0x0004,
    KC_B = 0x0005,
    KC_C = 0x0006,
    KC_D = 0x0007,
    KC_E = 0x0008,
    KC_F = 0x0009,
    KC_G = 0x000A,
    KC_H = 0x000B,
    KC_I = 0x000C,
    KC_J = 0x000D,
    KC_K = 0x000E,
    KC_L = 0x000F,
    KC_M = 0x0010,
    KC_N = 0x0011,
    KC_O = 0x0012,
    KC_P = 0x0013,
    KC_R = 0x0015,
    KC_S = 0x0016,
    KC_T = 0x0017,
    KC_U = 0x0018,
    KC_V = 0x0019,
    KC_W = 0x001A,
    KC_X = 0x001B,
    KC_Y = 0x001C,
    KC_Z = 0x001D,
    KC_1 = 0x001E,
    KC_2 = 0x001F,
    KC_3 = 0x0020,
    KC_4 = 0x0021,
    KC_5 = 0x0022,
    KC_6 = 0x0023,
    KC_7 = 0x0024,
    KC_8 = 0x0025,
    KC_9 = 0x0026,
    KC_0 = 0x0027,
    KC_ENTER = 0x0028,
    KC_ESCAPE = 0x0029,
    KC_BSPACE = 0x002A,
    KC_TAB = 0x002B,
    KC_SPACE = 0x002C,
    KC_MINUS = 0x002D,
    KC_EQUAL = 0x002E,
    KC_LBRACKET = 0x002F,
    KC_RBRACKET = 0x0030,
    KC_BSLASH = 0x0031,
    KC_NONUS_HASH = 0x0032,
    KC_SCOLON = 0x0033,
    KC_QUOTE = 0x0034,
    KC_GRAVE = 0x0035,
    KC_COMMA = 0x0036,
    KC_DOT = 0x0037,
    KC_SLASH = 0x0038,
    KC_CAPSLOCK = 0x0039,
    KC_F1 = 0x003A,
    KC_F2 = 0x003B,
    KC_F3 = 0x003C,
    KC_F4 = 0x003D,
    KC_F5 = 0x003E,
    KC_F6 = 0x003F,
    KC_F7 = 0x0040,
    KC_F8 = 0x0041,
    KC_F9 = 0x0042,
    KC_F10 = 0x0043,
    KC_F11 = 0x0044,
    KC_F12 = 0x0045,
    KC_PSCREEN = 0x0046,
    KC_SCROLLLOCK = 0x0047,
    KC_PAUSE = 0x0048,
    KC_INSERT = 0x0049,
    KC_HOME = 0x004A,
    KC_PGUP = 0x004B,
    KC_DELETE = 0x004C,
    KC_PGDOWN = 0x004E,
    KC_RIGHT = 0x004F,
    KC_LEFT = 0x0050,
    KC_DOWN = 0x0051,
    KC_UP = 0x0052,
    KC_NUMLOCK = 0x0053,
    KC_KP_SLASH = 0x0054,
    KC_KP_ASTERISK = 0x0055,
    KC_KP_MINUS = 0x0056,
    KC_KP_PLUS = 0x0057,
    KC_KP_ENTER = 0x0058,
    KC_KP_1 = 0x0059,
    KC_KP_2 = 0x005A,
    KC_KP_3 = 0x005B,
    KC_KP_4 = 0x005C,
    KC_KP_5 = 0x005D,
    KC_KP_6 = 0x005E,
    KC_KP_7 = 0x005F,
    KC_KP_8 = 0x0060,
    KC_KP_9 = 0x0061,
    KC_KP_0 = 0x0062,
    KC_KP_DOT = 0x0063,
    KC_NONUS_BSLASH = 0x0064,
    KC_APPLICATION = 0x0065,
    KC_POWER = 0x0066,
    KC_KP_EQUAL = 0x0067,
    KC_F13 = 0x0068,
    KC_F14 = 0x0069,
    KC_F15 = 0x006A,
    KC_F16 = 0x006B,
    KC_F17 = 0x006C,
    KC_F18 = 0x006D,
    KC_F19 = 0x006E,
    KC_F20 = 0x006F,
    KC_F21 = 0x0070,
    KC_F22 = 0x0071,
    KC_F23 = 0x0072,
    KC_F24 = 0x0073,
    KC_EXECUTE = 0x0074,
    KC_HELP = 0x0075,
    KC_MENU = 0x0076,
    KC_SELECT = 0x0077,
    KC_STOP = 0x0078,
    KC_AGAIN = 0x0079,
    KC_UNDO = 0x007A,
    KC_CUT = 0x007B,
    KC_COPY = 0x007C,
    KC_PASTE = 0x007D,
    KC_FIND = 0x007E,
    KC__MUTE = 0x007F,
    KC__VOLUP = 0x0080,
    KC__VOLDOWN = 0x0081,
    KC_LOCKING_CAPS = 0x0082,
    KC_LOCKING_NUM = 0x0083,
    KC_LOCKING_SCROLL = 0x0084,
    KC_KP_COMMA = 0x0085,
    KC_KP_EQUAL_AS400 = 0x0086,
    KC_INT1 = 0x0087,
    KC_INT2 = 0x0088,
    KC_INT3 = 0x0089,
    KC_INT4 = 0x008A,
    KC_INT5 = 0x008B,
    KC_INT6 = 0x008C,
    KC_INT7 = 0x008D,
    KC_INT8 = 0x008E,
    KC_INT9 = 0x008F,
    KC_LANG1 = 0x0090,
    KC_LANG2 = 0x0091,
    KC_LANG3 = 0x0092,
    KC_LANG4 = 0x0093,
    KC_LANG5 = 0x0094,
    KC_LANG6 = 0x0095,
    KC_LANG7 = 0x0096,
    KC_LANG8 = 0x0097,
    KC_LANG9 = 0x0098,
    KC_ALT_ERASE = 0x0099,
    KC_SYSREQ = 0x009A,
    KC_CANCEL = 0x009B,
    KC_CLEAR = 0x009C,
    KC_PRIOR = 0x009D,
    KC_RETURN = 0x009E,
    KC_SEPARATOR = 0x009F,
    KC_OUT = 0x00A0,
    KC_OPER = 0x00A1,
    KC_CLEAR_AGAIN = 0x00A2,
    KC_CRSEL = 0x00A3,
    KC_EXSEL = 0x00A4,
    KC_LCTRL = 0x00E0,
    KC_LSHIFT = 0x00E1,
    KC_LALT = 0x00E2,
    KC_LGUI = 0x00E3,
    KC_RCTRL = 0x00E4,
    KC_RSHIFT = 0x00E5,
    KC_RALT = 0x00E6,
    KC_RGUI = 0x00E7,
    KC_AUDIO_MUTE = 0x10E2,
    KC_AUDIO_VOL_UP = 0x10E9,
    KC_AUDIO_VOL_DOWN = 0x10EA,
    KC_MEDIA_NEXT_TRACK = 0x10B5,
    KC_MEDIA_PREV_TRACK = 0x10B6,
    KC_MEDIA_STOP = 0x10B7,
    KC_MEDIA_PLAY_PAUSE = 0x10CD,
    KC_LVL1 = 0x2001,
    KC_LVL2 = 0x2002,
    KC_LVL3 = 0x2003,
    KC_BOOTLOADER1 = 0x2004,
    KC_BOOTLOADER2 = 0x2005,
    KC_BACKLIGHT_DISABLE = 0x2006,
    KC_BACKLIGHT_ENABLE = 0x2007,
    KC_BACKLIGHT_BRDOWN = 0x2008,
    KC_BACKLIGHT_BRUP = 0x2009,
    KC_WIN_LOCK = 0x200A,
    KC_KEYBOARD_LOCK = 0x200B,
    KC_TURBO_SELECT_MODE = 0x200C,
    KC_LAYER_1 = 0x3001,
    KC_LAYER_2 = 0x3002,
    KC_LAYER_3 = 0x3003,
    KC_LAYER_4 = 0x3004,
    KC_LAYER_5 = 0x3005,
    KC_LAYER_6 = 0x3006,
    KC_LAYER_7 = 0x3007,
    KC_LAYER_8 = 0x3008,
    KC_LAYER_9 = 0x3009,
} Keycodes;
