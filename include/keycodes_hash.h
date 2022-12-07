/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf /tmp/tmp_jm7yx2c/keycodes.gperf  */
/* Computed positions: -k'4-6,10,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 8 "/tmp/tmp_jm7yx2c/keycodes.gperf"

#include <stdint.h>
#line 11 "/tmp/tmp_jm7yx2c/keycodes.gperf"
struct keycode { char *name; uint16_t keycode; };
#include <string.h>

#define TOTAL_KEYWORDS 199
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 20
#define MIN_HASH_VALUE 4
#define MAX_HASH_VALUE 740
/* maximum key range = 737, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
keycode_hash (register const char *str, register size_t len)
{
  static const unsigned short asso_values[] =
    {
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 125, 155,
      145, 210, 190, 215, 200, 225, 235, 250,   0, 741,
      741, 741, 741, 741, 741,  60,  80,  90,  50,   5,
       85,  70, 205, 135, 230, 110,  75,  10,  55,  45,
        0,  10, 105,  15,  25,  35,  65, 115, 150, 120,
       95, 741, 741, 741, 741,  25,  85, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741, 741, 741, 741,
      741, 741, 741, 741, 741, 741, 741
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
      case 8:
      case 7:
      case 6:
        hval += asso_values[(unsigned char)str[5]+1];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

const struct keycode *
keycode_lookup (register const char *str, register size_t len)
{
  static const struct keycode wordlist[] =
    {
#line 32 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_P", 0x0013},
#line 21 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_E", 0x0008},
#line 29 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_M", 0x0010},
#line 34 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_S", 0x0016},
#line 93 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_UP", 0x0052},
#line 190 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_MEDIA_PLAY_PAUSE", 0x10CD},
#line 131 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_STOP", 0x0078},
#line 189 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_MEDIA_STOP", 0x10B7},
#line 35 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_T", 0x0017},
#line 64 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_QUOTE", 0x0034},
#line 130 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SELECT", 0x0077},
#line 36 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_U", 0x0018},
#line 88 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_DELETE", 0x004C},
#line 53 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_ESCAPE", 0x0029},
#line 31 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_O", 0x0012},
#line 136 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_PASTE", 0x007D},
#line 139 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC__VOLUP", 0x0080},
#line 129 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_MENU", 0x0076},
#line 20 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_D", 0x0007},
#line 56 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SPACE", 0x002C},
#line 138 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC__MUTE", 0x007F},
#line 30 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_N", 0x0011},
#line 202 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_TURBO_SELECT_MODE", 0x200C},
#line 54 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BSPACE", 0x002A},
#line 17 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_A", 0x0004},
#line 184 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_AUDIO_MUTE", 0x10E2},
#line 37 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_V", 0x0019},
#line 84 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_PAUSE", 0x0048},
#line 89 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_PGDOWN", 0x004E},
#line 87 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_PGUP", 0x004B},
#line 23 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_G", 0x000A},
#line 171 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_OUT", 0x00A0},
#line 133 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_UNDO", 0x007A},
#line 188 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_MEDIA_PREV_TRACK", 0x10B6},
#line 13 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_NO", 0x0000},
#line 28 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_L", 0x000F},
#line 67 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_DOT", 0x0037},
#line 58 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_EQUAL", 0x002E},
#line 18 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_B", 0x0005},
#line 63 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SCOLON", 0x0033},
#line 170 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SEPARATOR", 0x009F},
#line 22 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F", 0x0009},
#line 178 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LALT", 0x00E2},
#line 165 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SYSREQ", 0x009A},
#line 185 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_AUDIO_VOL_UP", 0x10E9},
#line 91 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LEFT", 0x0050},
#line 19 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_C", 0x0006},
#line 82 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_PSCREEN", 0x0046},
#line 134 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_CUT", 0x007B},
#line 41 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_Z", 0x001D},
#line 112 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_APPLICATION", 0x0065},
#line 187 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_MEDIA_NEXT_TRACK", 0x10B5},
#line 182 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RALT", 0x00E6},
#line 52 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_ENTER", 0x0028},
#line 169 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RETURN", 0x009E},
#line 59 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LBRACKET", 0x002F},
#line 16 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_UNDEFINED", 0x0003},
#line 57 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_MINUS", 0x002D},
#line 33 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_R", 0x0015},
#line 15 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_POST_FAIL", 0x0002},
#line 27 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_K", 0x000E},
#line 128 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_HELP", 0x0075},
#line 110 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_DOT", 0x0063},
#line 38 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_W", 0x001A},
#line 98 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_PLUS", 0x0057},
#line 186 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_AUDIO_VOL_DOWN", 0x10EA},
#line 60 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RBRACKET", 0x0030},
#line 172 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_OPER", 0x00A1},
#line 40 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_Y", 0x001C},
#line 164 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_ALT_ERASE", 0x0099},
#line 85 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INSERT", 0x0049},
#line 51 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_0", 0x0027},
#line 97 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_MINUS", 0x0056},
#line 66 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_COMMA", 0x0036},
#line 177 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LSHIFT", 0x00E1},
#line 127 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_EXECUTE", 0x0074},
#line 55 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_TAB", 0x002B},
#line 175 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_EXSEL", 0x00A4},
#line 142 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LOCKING_NUM", 0x0083},
#line 65 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_GRAVE", 0x0035},
#line 141 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LOCKING_CAPS", 0x0082},
#line 140 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC__VOLDOWN", 0x0081},
#line 135 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_COPY", 0x007C},
#line 132 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_AGAIN", 0x0079},
#line 25 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_I", 0x000C},
#line 144 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_COMMA", 0x0085},
#line 199 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BACKLIGHT_BRUP", 0x2009},
#line 166 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_CANCEL", 0x009B},
#line 176 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LCTRL", 0x00E0},
#line 197 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BACKLIGHT_ENABLE", 0x2007},
#line 196 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BACKLIGHT_DISABLE", 0x2006},
#line 181 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RSHIFT", 0x00E5},
#line 43 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_2", 0x001F},
#line 192 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LVL2", 0x2002},
#line 174 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_CRSEL", 0x00A3},
#line 39 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_X", 0x001B},
#line 92 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_DOWN", 0x0051},
#line 113 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_POWER", 0x0066},
#line 191 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LVL1", 0x2001},
#line 180 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RCTRL", 0x00E4},
#line 42 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_1", 0x001E},
#line 99 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_ENTER", 0x0058},
#line 86 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_HOME", 0x004A},
#line 83 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SCROLLLOCK", 0x0047},
#line 61 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BSLASH", 0x0031},
#line 137 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_FIND", 0x007E},
#line 96 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_ASTERISK", 0x0055},
#line 109 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_0", 0x0062},
#line 143 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LOCKING_SCROLL", 0x0084},
#line 156 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG2", 0x0091},
#line 198 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BACKLIGHT_BRDOWN", 0x2008},
#line 114 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_EQUAL", 0x0067},
#line 14 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_ROLL_OVER", 0x0001},
#line 155 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG1", 0x0090},
#line 195 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BOOTLOADER2", 0x2005},
#line 101 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_2", 0x005A},
#line 179 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LGUI", 0x00E3},
#line 194 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_BOOTLOADER1", 0x2004},
#line 100 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_1", 0x0059},
#line 167 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_CLEAR", 0x009C},
#line 193 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LVL3", 0x2003},
#line 69 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_CAPSLOCK", 0x0039},
#line 94 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_NUMLOCK", 0x0053},
#line 147 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT2", 0x0088},
#line 158 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG4", 0x0093},
#line 173 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_CLEAR_AGAIN", 0x00A2},
#line 71 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F2", 0x003B},
#line 183 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RGUI", 0x00E7},
#line 68 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_SLASH", 0x0038},
#line 45 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_4", 0x0021},
#line 146 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT1", 0x0087},
#line 160 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG6", 0x0095},
#line 103 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_4", 0x005C},
#line 145 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_EQUAL_AS400", 0x0086},
#line 157 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG3", 0x0092},
#line 70 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F1", 0x003A},
#line 105 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_6", 0x005E},
#line 159 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG5", 0x0094},
#line 47 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_6", 0x0023},
#line 102 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_3", 0x005B},
#line 161 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG7", 0x0096},
#line 24 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_H", 0x000B},
#line 104 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_5", 0x005D},
#line 149 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT4", 0x008A},
#line 162 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG8", 0x0097},
#line 44 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_3", 0x0020},
#line 95 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_SLASH", 0x0054},
#line 106 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_7", 0x005F},
#line 151 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT6", 0x008C},
#line 46 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_5", 0x0022},
#line 107 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_8", 0x0060},
#line 163 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LANG9", 0x0098},
#line 201 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KEYBOARD_LOCK", 0x200B},
#line 148 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT3", 0x0089},
#line 111 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_NONUS_BSLASH", 0x0064},
#line 150 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT5", 0x008B},
#line 168 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_PRIOR", 0x009D},
#line 108 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_KP_9", 0x0061},
#line 48 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_7", 0x0024},
#line 152 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT7", 0x008D},
#line 26 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_J", 0x000D},
#line 153 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT8", 0x008E},
#line 73 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F4", 0x003D},
#line 49 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_8", 0x0025},
#line 90 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_RIGHT", 0x004F},
#line 154 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_INT9", 0x008F},
#line 75 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F6", 0x003F},
#line 121 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F19", 0x006E},
#line 50 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_9", 0x0026},
#line 200 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_WIN_LOCK", 0x200A},
#line 72 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F3", 0x003C},
#line 122 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F20", 0x006F},
#line 74 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F5", 0x003E},
#line 79 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F10", 0x0043},
#line 204 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_2", 0x3002},
#line 123 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F21", 0x0070},
#line 76 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F7", 0x0040},
#line 80 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F11", 0x0044},
#line 203 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_1", 0x3001},
#line 77 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F8", 0x0041},
#line 62 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_NONUS_HASH", 0x0032},
#line 78 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F9", 0x0042},
#line 124 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F22", 0x0071},
#line 81 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F12", 0x0045},
#line 206 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_4", 0x3004},
#line 125 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F23", 0x0072},
#line 208 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_6", 0x3006},
#line 126 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F24", 0x0073},
#line 115 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F13", 0x0068},
#line 116 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F14", 0x0069},
#line 205 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_3", 0x3003},
#line 117 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F15", 0x006A},
#line 207 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_5", 0x3005},
#line 118 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F16", 0x006B},
#line 209 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_7", 0x3007},
#line 119 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F17", 0x006C},
#line 210 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_8", 0x3008},
#line 120 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_F18", 0x006D},
#line 211 "/tmp/tmp_jm7yx2c/keycodes.gperf"
      {"KC_LAYER_9", 0x3009}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = keycode_hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          register const struct keycode *resword;

          if (key < 314)
            {
              if (key < 172)
                {
                  if (key < 113)
                    {
                      switch (key - 4)
                        {
                          case 0:
                            resword = &wordlist[0];
                            goto compare;
                          case 10:
                            resword = &wordlist[1];
                            goto compare;
                          case 20:
                            resword = &wordlist[2];
                            goto compare;
                          case 30:
                            resword = &wordlist[3];
                            goto compare;
                          case 36:
                            resword = &wordlist[4];
                            goto compare;
                          case 40:
                            resword = &wordlist[5];
                            goto compare;
                          case 43:
                            resword = &wordlist[6];
                            goto compare;
                          case 44:
                            resword = &wordlist[7];
                            goto compare;
                          case 50:
                            resword = &wordlist[8];
                            goto compare;
                          case 54:
                            resword = &wordlist[9];
                            goto compare;
                          case 60:
                            resword = &wordlist[10];
                            goto compare;
                          case 70:
                            resword = &wordlist[11];
                            goto compare;
                          case 75:
                            resword = &wordlist[12];
                            goto compare;
                          case 80:
                            resword = &wordlist[13];
                            goto compare;
                          case 90:
                            resword = &wordlist[14];
                            goto compare;
                          case 94:
                            resword = &wordlist[15];
                            goto compare;
                          case 95:
                            resword = &wordlist[16];
                            goto compare;
                          case 98:
                            resword = &wordlist[17];
                            goto compare;
                          case 100:
                            resword = &wordlist[18];
                            goto compare;
                          case 104:
                            resword = &wordlist[19];
                            goto compare;
                        }
                    }
                  else
                    {
                      switch (key - 113)
                        {
                          case 0:
                            resword = &wordlist[20];
                            goto compare;
                          case 1:
                            resword = &wordlist[21];
                            goto compare;
                          case 2:
                            resword = &wordlist[22];
                            goto compare;
                          case 6:
                            resword = &wordlist[23];
                            goto compare;
                          case 11:
                            resword = &wordlist[24];
                            goto compare;
                          case 15:
                            resword = &wordlist[25];
                            goto compare;
                          case 21:
                            resword = &wordlist[26];
                            goto compare;
                          case 25:
                            resword = &wordlist[27];
                            goto compare;
                          case 26:
                            resword = &wordlist[28];
                            goto compare;
                          case 29:
                            resword = &wordlist[29];
                            goto compare;
                          case 31:
                            resword = &wordlist[30];
                            goto compare;
                          case 33:
                            resword = &wordlist[31];
                            goto compare;
                          case 34:
                            resword = &wordlist[32];
                            goto compare;
                          case 36:
                            resword = &wordlist[33];
                            goto compare;
                          case 37:
                            resword = &wordlist[34];
                            goto compare;
                          case 41:
                            resword = &wordlist[35];
                            goto compare;
                          case 48:
                            resword = &wordlist[36];
                            goto compare;
                          case 50:
                            resword = &wordlist[37];
                            goto compare;
                          case 51:
                            resword = &wordlist[38];
                            goto compare;
                          case 56:
                            resword = &wordlist[39];
                            goto compare;
                        }
                    }
                }
              else
                {
                  if (key < 224)
                    {
                      switch (key - 172)
                        {
                          case 0:
                            resword = &wordlist[40];
                            goto compare;
                          case 2:
                            resword = &wordlist[41];
                            goto compare;
                          case 5:
                            resword = &wordlist[42];
                            goto compare;
                          case 7:
                            resword = &wordlist[43];
                            goto compare;
                          case 8:
                            resword = &wordlist[44];
                            goto compare;
                          case 10:
                            resword = &wordlist[45];
                            goto compare;
                          case 12:
                            resword = &wordlist[46];
                            goto compare;
                          case 13:
                            resword = &wordlist[47];
                            goto compare;
                          case 19:
                            resword = &wordlist[48];
                            goto compare;
                          case 22:
                            resword = &wordlist[49];
                            goto compare;
                          case 27:
                            resword = &wordlist[50];
                            goto compare;
                          case 32:
                            resword = &wordlist[51];
                            goto compare;
                          case 35:
                            resword = &wordlist[52];
                            goto compare;
                          case 36:
                            resword = &wordlist[53];
                            goto compare;
                          case 37:
                            resword = &wordlist[54];
                            goto compare;
                          case 39:
                            resword = &wordlist[55];
                            goto compare;
                          case 40:
                            resword = &wordlist[56];
                            goto compare;
                          case 41:
                            resword = &wordlist[57];
                            goto compare;
                          case 42:
                            resword = &wordlist[58];
                            goto compare;
                          case 45:
                            resword = &wordlist[59];
                            goto compare;
                        }
                    }
                  else
                    {
                      if (key < 270)
                        {
                          switch (key - 224)
                            {
                              case 0:
                                resword = &wordlist[60];
                                goto compare;
                              case 3:
                                resword = &wordlist[61];
                                goto compare;
                              case 5:
                                resword = &wordlist[62];
                                goto compare;
                              case 10:
                                resword = &wordlist[63];
                                goto compare;
                              case 11:
                                resword = &wordlist[64];
                                goto compare;
                              case 13:
                                resword = &wordlist[65];
                                goto compare;
                              case 17:
                                resword = &wordlist[66];
                                goto compare;
                              case 18:
                                resword = &wordlist[67];
                                goto compare;
                              case 20:
                                resword = &wordlist[68];
                                goto compare;
                              case 23:
                                resword = &wordlist[69];
                                goto compare;
                              case 25:
                                resword = &wordlist[70];
                                goto compare;
                              case 30:
                                resword = &wordlist[71];
                                goto compare;
                              case 32:
                                resword = &wordlist[72];
                                goto compare;
                              case 34:
                                resword = &wordlist[73];
                                goto compare;
                              case 35:
                                resword = &wordlist[74];
                                goto compare;
                              case 36:
                                resword = &wordlist[75];
                                goto compare;
                              case 37:
                                resword = &wordlist[76];
                                goto compare;
                              case 39:
                                resword = &wordlist[77];
                                goto compare;
                              case 40:
                                resword = &wordlist[78];
                                goto compare;
                              case 44:
                                resword = &wordlist[79];
                                goto compare;
                            }
                        }
                      else
                        {
                          switch (key - 270)
                            {
                              case 0:
                                resword = &wordlist[80];
                                goto compare;
                              case 1:
                                resword = &wordlist[81];
                                goto compare;
                              case 2:
                                resword = &wordlist[82];
                                goto compare;
                              case 3:
                                resword = &wordlist[83];
                                goto compare;
                              case 4:
                                resword = &wordlist[84];
                                goto compare;
                              case 6:
                                resword = &wordlist[85];
                                goto compare;
                              case 7:
                                resword = &wordlist[86];
                                goto compare;
                              case 9:
                                resword = &wordlist[87];
                                goto compare;
                              case 13:
                                resword = &wordlist[88];
                                goto compare;
                              case 14:
                                resword = &wordlist[89];
                                goto compare;
                              case 15:
                                resword = &wordlist[90];
                                goto compare;
                              case 19:
                                resword = &wordlist[91];
                                goto compare;
                              case 24:
                                resword = &wordlist[92];
                                goto compare;
                              case 32:
                                resword = &wordlist[93];
                                goto compare;
                              case 33:
                                resword = &wordlist[94];
                                goto compare;
                              case 34:
                                resword = &wordlist[95];
                                goto compare;
                              case 37:
                                resword = &wordlist[96];
                                goto compare;
                              case 38:
                                resword = &wordlist[97];
                                goto compare;
                              case 42:
                                resword = &wordlist[98];
                                goto compare;
                              case 43:
                                resword = &wordlist[99];
                                goto compare;
                            }
                        }
                    }
                }
            }
          else
            {
              if (key < 413)
                {
                  if (key < 367)
                    {
                      switch (key - 314)
                        {
                          case 0:
                            resword = &wordlist[100];
                            goto compare;
                          case 2:
                            resword = &wordlist[101];
                            goto compare;
                          case 3:
                            resword = &wordlist[102];
                            goto compare;
                          case 4:
                            resword = &wordlist[103];
                            goto compare;
                          case 5:
                            resword = &wordlist[104];
                            goto compare;
                          case 8:
                            resword = &wordlist[105];
                            goto compare;
                          case 10:
                            resword = &wordlist[106];
                            goto compare;
                          case 13:
                            resword = &wordlist[107];
                            goto compare;
                          case 18:
                            resword = &wordlist[108];
                            goto compare;
                          case 19:
                            resword = &wordlist[109];
                            goto compare;
                          case 20:
                            resword = &wordlist[110];
                            goto compare;
                          case 27:
                            resword = &wordlist[111];
                            goto compare;
                          case 28:
                            resword = &wordlist[112];
                            goto compare;
                          case 29:
                            resword = &wordlist[113];
                            goto compare;
                          case 30:
                            resword = &wordlist[114];
                            goto compare;
                          case 33:
                            resword = &wordlist[115];
                            goto compare;
                          case 38:
                            resword = &wordlist[116];
                            goto compare;
                          case 40:
                            resword = &wordlist[117];
                            goto compare;
                          case 43:
                            resword = &wordlist[118];
                            goto compare;
                          case 49:
                            resword = &wordlist[119];
                            goto compare;
                        }
                    }
                  else
                    {
                      switch (key - 367)
                        {
                          case 0:
                            resword = &wordlist[120];
                            goto compare;
                          case 4:
                            resword = &wordlist[121];
                            goto compare;
                          case 8:
                            resword = &wordlist[122];
                            goto compare;
                          case 10:
                            resword = &wordlist[123];
                            goto compare;
                          case 11:
                            resword = &wordlist[124];
                            goto compare;
                          case 12:
                            resword = &wordlist[125];
                            goto compare;
                          case 13:
                            resword = &wordlist[126];
                            goto compare;
                          case 15:
                            resword = &wordlist[127];
                            goto compare;
                          case 16:
                            resword = &wordlist[128];
                            goto compare;
                          case 17:
                            resword = &wordlist[129];
                            goto compare;
                          case 20:
                            resword = &wordlist[130];
                            goto compare;
                          case 21:
                            resword = &wordlist[131];
                            goto compare;
                          case 25:
                            resword = &wordlist[132];
                            goto compare;
                          case 30:
                            resword = &wordlist[133];
                            goto compare;
                          case 31:
                            resword = &wordlist[134];
                            goto compare;
                          case 33:
                            resword = &wordlist[135];
                            goto compare;
                          case 35:
                            resword = &wordlist[136];
                            goto compare;
                          case 36:
                            resword = &wordlist[137];
                            goto compare;
                          case 37:
                            resword = &wordlist[138];
                            goto compare;
                          case 45:
                            resword = &wordlist[139];
                            goto compare;
                        }
                    }
                }
              else
                {
                  if (key < 464)
                    {
                      switch (key - 413)
                        {
                          case 0:
                            resword = &wordlist[140];
                            goto compare;
                          case 1:
                            resword = &wordlist[141];
                            goto compare;
                          case 4:
                            resword = &wordlist[142];
                            goto compare;
                          case 9:
                            resword = &wordlist[143];
                            goto compare;
                          case 10:
                            resword = &wordlist[144];
                            goto compare;
                          case 11:
                            resword = &wordlist[145];
                            goto compare;
                          case 13:
                            resword = &wordlist[146];
                            goto compare;
                          case 14:
                            resword = &wordlist[147];
                            goto compare;
                          case 19:
                            resword = &wordlist[148];
                            goto compare;
                          case 21:
                            resword = &wordlist[149];
                            goto compare;
                          case 24:
                            resword = &wordlist[150];
                            goto compare;
                          case 25:
                            resword = &wordlist[151];
                            goto compare;
                          case 28:
                            resword = &wordlist[152];
                            goto compare;
                          case 29:
                            resword = &wordlist[153];
                            goto compare;
                          case 32:
                            resword = &wordlist[154];
                            goto compare;
                          case 34:
                            resword = &wordlist[155];
                            goto compare;
                          case 35:
                            resword = &wordlist[156];
                            goto compare;
                          case 39:
                            resword = &wordlist[157];
                            goto compare;
                          case 41:
                            resword = &wordlist[158];
                            goto compare;
                          case 44:
                            resword = &wordlist[159];
                            goto compare;
                        }
                    }
                  else
                    {
                      if (key < 568)
                        {
                          switch (key - 464)
                            {
                              case 0:
                                resword = &wordlist[160];
                                goto compare;
                              case 3:
                                resword = &wordlist[161];
                                goto compare;
                              case 6:
                                resword = &wordlist[162];
                                goto compare;
                              case 10:
                                resword = &wordlist[163];
                                goto compare;
                              case 14:
                                resword = &wordlist[164];
                                goto compare;
                              case 18:
                                resword = &wordlist[165];
                                goto compare;
                              case 26:
                                resword = &wordlist[166];
                                goto compare;
                              case 32:
                                resword = &wordlist[167];
                                goto compare;
                              case 40:
                                resword = &wordlist[168];
                                goto compare;
                              case 42:
                                resword = &wordlist[169];
                                goto compare;
                              case 46:
                                resword = &wordlist[170];
                                goto compare;
                              case 52:
                                resword = &wordlist[171];
                                goto compare;
                              case 56:
                                resword = &wordlist[172];
                                goto compare;
                              case 62:
                                resword = &wordlist[173];
                                goto compare;
                              case 66:
                                resword = &wordlist[174];
                                goto compare;
                              case 72:
                                resword = &wordlist[175];
                                goto compare;
                              case 76:
                                resword = &wordlist[176];
                                goto compare;
                              case 82:
                                resword = &wordlist[177];
                                goto compare;
                              case 86:
                                resword = &wordlist[178];
                                goto compare;
                              case 96:
                                resword = &wordlist[179];
                                goto compare;
                            }
                        }
                      else
                        {
                          switch (key - 568)
                            {
                              case 0:
                                resword = &wordlist[180];
                                goto compare;
                              case 22:
                                resword = &wordlist[181];
                                goto compare;
                              case 23:
                                resword = &wordlist[182];
                                goto compare;
                              case 33:
                                resword = &wordlist[183];
                                goto compare;
                              case 52:
                                resword = &wordlist[184];
                                goto compare;
                              case 68:
                                resword = &wordlist[185];
                                goto compare;
                              case 72:
                                resword = &wordlist[186];
                                goto compare;
                              case 73:
                                resword = &wordlist[187];
                                goto compare;
                              case 78:
                                resword = &wordlist[188];
                                goto compare;
                              case 83:
                                resword = &wordlist[189];
                                goto compare;
                              case 92:
                                resword = &wordlist[190];
                                goto compare;
                              case 93:
                                resword = &wordlist[191];
                                goto compare;
                              case 102:
                                resword = &wordlist[192];
                                goto compare;
                              case 103:
                                resword = &wordlist[193];
                                goto compare;
                              case 122:
                                resword = &wordlist[194];
                                goto compare;
                              case 138:
                                resword = &wordlist[195];
                                goto compare;
                              case 142:
                                resword = &wordlist[196];
                                goto compare;
                              case 163:
                                resword = &wordlist[197];
                                goto compare;
                              case 172:
                                resword = &wordlist[198];
                                goto compare;
                            }
                        }
                    }
                }
            }
          return 0;
        compare:
          {
            register const char *s = resword->name;

            if (*str == *s && !strcmp (str + 1, s + 1))
              return resword;
          }
        }
    }
  return 0;
}
