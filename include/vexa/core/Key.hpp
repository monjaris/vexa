#pragma once
#include "common.hpp"
NAMESPACE_BEGIN(vexa)


/*
 * All key/keycode/modifier of the library is defined here
 * some of the keys are hardware-dependent dont forget to report any issues
 */


//  MODIFIERS  //
enum class KeyMod : uint16
{
    NONE = 0,

    SHIFT_L  = 1 << 0,
    SHIFT_R  = 1 << 1,

    CTRL_L =  1 << 6,
    CTRL_R =  1 << 7,

    ALT_L =  1 << 8,
    ALT_R =  1 << 9,

    META_L =  1 << 10,
    META_R =  1 << 11,

    NUM_LOCK    =  1 << 12,
    CAPS_LOCK   =  1 << 13,
    ALT_GR      =  1 << 14,
    SCROLL_LOCK =  1 << 15,

    CTRL  =  CTRL_L  | CTRL_R,
    SHIFT =  SHIFT_L | SHIFT_R,
    ALT   =  ALT_L   | ALT_R,
    META  =  META_L  | META_R,

    COUNT = 18
};





//  KEYS  // scancodes, not physical
enum class Key : uint16
{
    NONE = 0,

    //  Letters  //
    A = 4, B = 5, C = 6, D = 7, E = 8, F = 9, G = 10, H = 11, I = 12, J = 13,
    K = 14, L = 15, M = 16, N = 17, O = 18, P = 19, Q = 20, R = 21, S = 22,
    T = 23, U = 24, V = 25, W = 26, X = 27, Y = 28, Z = 29,

    //  Digits  //
    ONE = 30, TWO = 31, THREE = 32, FOUR = 33, FIVE = 34,
    SIX = 35, SEVEN = 36, EIGHT = 37, NINE = 38, TEN = 39,

    //  Generic  //
    ENTER = 40, ESC = 41, BACKSPACE = 42, TAB = 43, SPACE = 44,

    //  Operators  //
    MINUS = 45, EQUALS = 46, BRACKET_L = 47, BRACKET_R = 48, BACKSLASH = 49, SEMICOLON = 51,
    APOSTROPHE = 52, BACKTICK = 53, COMMA = 54, PERIOD = 55, SLASH = 56, CAPSLOCK = 57,

    //  Function [1-12]  //
    F1 = 58, F2 = 59, F3 = 60, F4 = 61, F5 = 62, F6 = 63,
    F7 = 64, F8 = 65, F9 = 66, F10 = 67, F11 = 68, F12 = 69,

    //  Control  //
    PRINT_SCREEN = 70, SCROLL_LOCK = 71, PAUSE = 72, INSERT = 73, HOME = 74,
    PAGEUP = 75, DELETE = 76, END = 77, PAGEDOWN = 78,
    RIGHT = 79, LEFT = 80, DOWN = 81, UP = 82,

    //  Keypad  //
    KP_NUM_LOCK = 83, KP_SLASH = 84, KP_ASTERISK = 85, KP_MINUS = 86, KP_PLUS = 87, KP_ENTER = 88,
    KP_1 = 89, KP_2 = 90, KP_3 = 91, KP_4 = 92, KP_5 = 93,
    KP_6 = 94, KP_7 = 95, KP_8 = 96, KP_9 = 97, KP_0 = 98, KP_PERIOD = 99,

    //  Niche  //
    NON_US_BACKSLASH = 100, APPLICATION = 101, MACOS_POWER = 102, KP_EQUALS = 103,

    //  Function [13-24]  //
    F13 = 104, F14 = 105, F15 = 106, F17 = 108, F18 = 109, F19 = 110,
    F20 = 111, F21 = 112, F22 = 113, F23 = 114, F24 = 115,

    //  Meta Control  //
    EXECUTE = 116, HELP = 117, MENU = 118, SELECT = 119,

    //  App Control  //
    STOP = 120, AGAIN = 121, UNDO = 122, CUT = 123, COPY = 124, PASTE = 125, FIND = 126,

    //  Audio Control  //
    MUTE = 127, VOLUMEUP = 128, VOLUMEDOWN = 129,

    //  Keypad-Niche  //
    KP_COMMA = 133, KP_EQUALSAS400 = 134,

    //  International  //
    INTERNATIONAL_1 = 135, INTERNATIONAL_2 = 136, INTERNATIONAL_3 = 137,
    INTERNATIONAL_4 = 138, INTERNATIONAL_5 = 139, INTERNATIONAL_6 = 140,
    INTERNATIONAL_7 = 141, INTERNATIONAL_8 = 142, INTERNATIONAL_9 = 143,

    //  LANG_*  //
    LANG_1 = 144,  // Hangul/English toggle
    LANG_2 = 145,  // Hanja conversion
    LANG_3 = 146,  // Katakana
    LANG_4 = 147,  // Hiragana
    LANG_5 = 148,  // Zenkaku/Hankaku
    LANG_6 = 149,  // reserved
    LANG_7 = 150,  // reserved
    LANG_8 = 151,  // reserved
    LANG_9 = 152,  // reserved

    //  Deprecated  //
    ALT_ERASE = 153, SYSREQ = 154, CANCEL = 155, CLEAR = 156, PRIOR = 157,
    ALT_RETURN = 158, SEPARATOR = 159, OUT = 160, OPER = 161, CLEAR_AGAIN = 162,
    CRSEL = 163, EXSEL = 164,

    //  Units  //
    KP_00 = 176, KP_000 = 177,
    THOUSANDSSEPARATOR = 178, DECIMALSEPARATOR = 179,
    CURRENCYUNIT = 180, CURRENCYSUBUNIT = 181,

    //  Keypad-Ex  //
    KP_LEFTPAREN = 182, KP_RIGHTPAREN = 183, KP_LEFTBRACE = 184, KP_RIGHTBRACE = 185,
    KP_TAB = 186, KP_BACKSPACE = 187,
    KP_A = 188, KP_B = 189, KP_C = 190, KP_D = 191, KP_E = 192, KP_F = 193,
    KP_XOR = 194, KP_POWER = 195, KP_PERCENT = 196, KP_LESS = 197, KP_GREATER = 198,
    KP_AMPERSAND = 199, KP_DBLAMPERSAND = 200, KP_VERTICALBAR = 201, KP_DBLVERTICALBAR = 202,
    KP_COLON = 203, KP_HASH = 204, KP_SPACE = 205, KP_AT = 206, KP_EXCLAM = 207,
    KP_MEMSTORE = 208, KP_MEMRECALL = 209, KP_MEMCLEAR = 210, KP_MEMADD = 211, KP_MEMSUBTRACT = 212, KP_MEMMULTIPLY = 213, KP_MEMDIVIDE = 214,
    KP_PLUSMINUS = 215, KP_CLEAR = 216, KP_CLEARENTRY = 217,
    KP_BINARY = 218, KP_OCTAL = 219, KP_DECIMAL = 220, KP_HEXADECIMAL = 221,

    //  Modifiers  //
    CTRL_L = 224, SHIFT_L = 225, ALT_L = 226, GUI_L = 227,
    CTRL_R = 228, SHIFT_R = 229, ALT_R = 230, GUI_R = 231,
    MODE = 257,

    //  Suspention  //
    SLEEP = 258,
    WAKE = 259,

    //  Channel Control (eg. TVs)  //
    CHANNEL_INCREMENT = 260,  // Channel Increment
    CHANNEL_DECREMENT = 261,  // Channel Decrement

    //  Media  //
    MEDIA_PLAY = 262,            // Play
    MEDIA_PAUSE = 263,           // Pause
    MEDIA_RECORD = 264,          // Record
    MEDIA_FAST_FORWARD = 265,    // Fast Forward
    MEDIA_REWIND = 266,          // Rewind
    MEDIA_NEXT_TRACK = 267,      // Next Track
    MEDIA_PREVIOUS_TRACK = 268,  //  Previous Track
    MEDIA_STOP = 269,            // Stop
    MEDIA_EJECT = 270,           // Eject
    MEDIA_PLAY_PAUSE = 271,      // Play / Pause
    MEDIA_SELECT = 272,          // Media Select

    //  App Control //
    APP_NEW = 273,  //  AC New
    APP_OPEN = 274,  //  AC Open
    APP_CLOSE = 275,  //  AC Close
    APP_EXIT = 276,  //  AC Exit
    APP_SAVE = 277,  //  AC Save
    APP_PRINT = 278,  //  AC Print
    APP_PROPERTIES = 279,  //  AC Properties
    APP_SEARCH = 280,  // AC Search
    APP_HOME = 281,  // AC Home
    APP_BACK = 282,  // AC Back
    APP_FORWARD = 283,  // AC Forward
    APP_STOP = 284,  // AC Stop
    APP_REFRESH = 285,  // AC Refresh
    APP_BOOKMARKS = 286,  // AC Bookmarks

    //  MOBILE  //
    SOFT_L = 287, SOFT_R = 288,
    CALL_ACCEPT = 289,  // Used for accepting phone calls
    CALL_REJECT = 290,  // Used for rejecting phone calls

    // DYNAMIC KEYS //
    RESERVED = 400,

    COUNT = 512
};





//  KEYCODES  // physical key codes
enum class Keycode : uint32
{
    EXTENDED_MASK = (1u << 29),
    SCANCODE_MASK = (1u << 30),
    UNKNOWN = 0x0u,

    ENTER = 0xDu, ESC = 0x1Bu, BACKSPACE = 0x8u, TAB = 0x9u, SPACE = 0x20u,
    EXCLAIM = 0x21u, QUOTE = 0x22u, HASH = 0x23u, DOLLAR = 0x24u, PERCENT = 0x25u,
    AMPERSAND = 0x26u, APOSTROPHE = 0x27u, PARENTHES_L = 0x28u, PARENTHES_R = 0x29u,
    ASTERISK = 0x2Au, PLUS = 0x2Bu, COMMA = 0x2Cu, MINUS = 0x2Du, PERIOD = 0x2Eu, SLASH = 0x2Fu,

    ZERO = 0x30u, ONE = 0x31u, TWO = 0x32u, THREE = 0x33u, FOUR = 0x34u,
    FIVE = 0x35u, SIX = 0x36u, SEVEN = 0x37u, EIGHT = 0x38u, NINE = 0x39u,

    COLON = 0x3Au, SEMICOLON = 0x3Bu, LESS = 0x3Cu, EQUALS = 0x3Du, GREATER = 0x3Eu, QUESTION = 0x3Fu,
    AT = 0x40u, BRACKET_L = 0x5Bu, BACKSLASH = 0x5Cu, BRACKET_R = 0x5Du,
    CARET = 0x5Eu, UNDERSCORE = 0x5Fu, BACKTICK = 0x60u,

    A = 0x61u, B = 0x62u, C = 0x63u, D = 0x64u, E = 0x65u, F = 0x66u, G = 0x67u, H = 0x68u, I = 0x69u, J = 0x6Au,
    K = 0x6Bu, L = 0x6Cu, M = 0x6Du, N = 0x6Eu, O = 0x6Fu, P = 0x70u, Q = 0x71u, R = 0x72u, S = 0x73u,
    T = 0x74u, U = 0x75u, V = 0x76u, W = 0x77u, X = 0x78u, Y = 0x79u, Z = 0x7Au,

    BRACE_L = 0x7Bu, PIPE = 0x7Cu, BRACE_R = 0x7Du, TILDE = 0x7Eu, DELETE = 0x7Fu,
    PLUS_MINUS = 0xB1u,

    CAPS_LOCK = SCANCODE_MASK | 0x39u,
    F1 = SCANCODE_MASK | 0x3Au, F2 = SCANCODE_MASK | 0x3Bu, F3 = SCANCODE_MASK | 0x3Cu, F4 = SCANCODE_MASK | 0x3Du,
    F5 = SCANCODE_MASK | 0x3Eu, F6 = SCANCODE_MASK | 0x3Fu, F7 = SCANCODE_MASK | 0x40u, F8 = SCANCODE_MASK | 0x41u,
    F9 = SCANCODE_MASK | 0x42u, F10 = SCANCODE_MASK | 0x43u, F11 = SCANCODE_MASK | 0x44u, F12 = SCANCODE_MASK | 0x45u,

    PRINT_SCREEN = SCANCODE_MASK | 0x46u, SCROLL_LOCK = SCANCODE_MASK | 0x47u, PAUSE = SCANCODE_MASK | 0x48u,
    INSERT = SCANCODE_MASK | 0x49u, HOME = SCANCODE_MASK | 0x4Au, PAGE_UP = SCANCODE_MASK | 0x4Bu,
    END = SCANCODE_MASK | 0x4Du, PAGE_DOWN = SCANCODE_MASK | 0x4Eu,
    RIGHT = SCANCODE_MASK | 0x4Fu, LEFT = SCANCODE_MASK | 0x50u, DOWN = SCANCODE_MASK | 0x51u, UP = SCANCODE_MASK | 0x52u,

    NUMLOCK_CLEAR = SCANCODE_MASK | 0x53u, KP_SLASH = SCANCODE_MASK | 0x54u, KP_ASTERISK = SCANCODE_MASK | 0x55u,
    KP_MINUS = SCANCODE_MASK | 0x56u, KP_PLUS = SCANCODE_MASK | 0x57u, KP_ENTER = SCANCODE_MASK | 0x58u,
    KP_1 = SCANCODE_MASK | 0x59u, KP_2 = SCANCODE_MASK | 0x5Au, KP_3 = SCANCODE_MASK | 0x5Bu,
    KP_4 = SCANCODE_MASK | 0x5Cu, KP_5 = SCANCODE_MASK | 0x5Du, KP_6 = SCANCODE_MASK | 0x5Eu,
    KP_7 = SCANCODE_MASK | 0x5Fu, KP_8 = SCANCODE_MASK | 0x60u, KP_9 = SCANCODE_MASK | 0x61u,
    KP_0 = SCANCODE_MASK | 0x62u, KP_PERIOD = SCANCODE_MASK | 0x63u,

    APPLICATION = SCANCODE_MASK | 0x65u, POWER = SCANCODE_MASK | 0x66u, KP_EQUALS = SCANCODE_MASK | 0x67u,
    F13 = SCANCODE_MASK | 0x68u, F14 = SCANCODE_MASK | 0x69u, F15 = SCANCODE_MASK | 0x6Au, F16 = SCANCODE_MASK | 0x6Bu,
    F17 = SCANCODE_MASK | 0x6Cu, F18 = SCANCODE_MASK | 0x6Du, F19 = SCANCODE_MASK | 0x6Eu, F20 = SCANCODE_MASK | 0x6Fu,
    F21 = SCANCODE_MASK | 0x70u, F22 = SCANCODE_MASK | 0x71u, F23 = SCANCODE_MASK | 0x72u, F24 = SCANCODE_MASK | 0x73u,

    EXECUTE = SCANCODE_MASK | 0x74u, HELP = SCANCODE_MASK | 0x75u, MENU = SCANCODE_MASK | 0x76u, SELECT = SCANCODE_MASK | 0x77u,
    STOP = SCANCODE_MASK | 0x78u, REDO = SCANCODE_MASK | 0x79u, UNDO = SCANCODE_MASK | 0x7Au, CUT = SCANCODE_MASK | 0x7Bu,
    COPY = SCANCODE_MASK | 0x7Cu, PASTE = SCANCODE_MASK | 0x7Du, FIND = SCANCODE_MASK | 0x7Eu,

    MUTE = SCANCODE_MASK | 0x7Fu, VOLUMEUP = SCANCODE_MASK | 0x80u, VOLUMEDOWN = SCANCODE_MASK | 0x81u,
    KP_COMMA = SCANCODE_MASK | 0x85u, SYSREQ = SCANCODE_MASK | 0x9Au,

    THOUSANDSSEPARATOR = SCANCODE_MASK | 0xB2u, DECIMALSEPARATOR = SCANCODE_MASK | 0xB3u,
    CURRENCYUNIT = SCANCODE_MASK | 0xB4u, CURRENCYSUBUNIT = SCANCODE_MASK | 0xB5u,

    KP_LEFTPAREN = SCANCODE_MASK | 0xB6u, KP_RIGHTPAREN = SCANCODE_MASK | 0xB7u,
    KP_LEFTBRACE = SCANCODE_MASK | 0xB8u, KP_RIGHTBRACE = SCANCODE_MASK | 0xB9u,
    KP_TAB = SCANCODE_MASK | 0xBAu, KP_BACKSPACE = SCANCODE_MASK | 0xBBu,
    KP_A = SCANCODE_MASK | 0xBCu, KP_B = SCANCODE_MASK | 0xBDu, KP_C = SCANCODE_MASK | 0xBEu,
    KP_D = SCANCODE_MASK | 0xBFu, KP_E = SCANCODE_MASK | 0xC0u, KP_F = SCANCODE_MASK | 0xC1u,
    KP_XOR = SCANCODE_MASK | 0xC2u, KP_POWER = SCANCODE_MASK | 0xC3u, KP_PERCENT = SCANCODE_MASK | 0xC4u,
    KP_LESS = SCANCODE_MASK | 0xC5u, KP_GREATER = SCANCODE_MASK | 0xC6u, KP_AMPERSAND = SCANCODE_MASK | 0xC7u,
    KP_DBLAMPERSAND = SCANCODE_MASK | 0xC8u, KP_VERTICALBAR = SCANCODE_MASK | 0xC9u, KP_DBLVERTICALBAR = SCANCODE_MASK | 0xCAu,
    KP_COLON = SCANCODE_MASK | 0xCBu, KP_HASH = SCANCODE_MASK | 0xCCu, KP_SPACE = SCANCODE_MASK | 0xCDu,
    KP_AT = SCANCODE_MASK | 0xCEu, KP_EXCLAM = SCANCODE_MASK | 0xCFu,
    KP_MEMSTORE = SCANCODE_MASK | 0xD0u, KP_MEMRECALL = SCANCODE_MASK | 0xD1u, KP_MEMCLEAR = SCANCODE_MASK | 0xD2u,
    KP_MEMADD = SCANCODE_MASK | 0xD3u, KP_MEMSUBTRACT = SCANCODE_MASK | 0xD4u, KP_MEMMULTIPLY = SCANCODE_MASK | 0xD5u,
    KP_MEMDIVIDE = SCANCODE_MASK | 0xD6u, KP_PLUSMINUS = SCANCODE_MASK | 0xD7u, KP_CLEAR = SCANCODE_MASK | 0xD8u,
    KP_CLEARENTRY = SCANCODE_MASK | 0xD9u, KP_BINARY = SCANCODE_MASK | 0xDAu, KP_OCTAL = SCANCODE_MASK | 0xDBu,
    KP_DECIMAL = SCANCODE_MASK | 0xDCu, KP_HEXADECIMAL = SCANCODE_MASK | 0xDDu,

    CTRL_L = SCANCODE_MASK | 0xE0u, SHIFT_L = SCANCODE_MASK | 0xE1u, ALT_L = SCANCODE_MASK | 0xE2u, GUI_L = SCANCODE_MASK | 0xE3u,
    CTRL_R = SCANCODE_MASK | 0xE4u, SHIFT_R = SCANCODE_MASK | 0xE5u, ALT_R = SCANCODE_MASK | 0xE6u, GUI_R = SCANCODE_MASK | 0xE7u,

    MODE = SCANCODE_MASK | 0x101u, SLEEP = SCANCODE_MASK | 0x102u, WAKE = SCANCODE_MASK | 0x103u,
    CHANNEL_INCREMENT = SCANCODE_MASK | 0x104u, CHANNEL_DECREMENT = SCANCODE_MASK | 0x105u,

    MEDIA_PLAY = SCANCODE_MASK | 0x106u, MEDIA_PAUSE = SCANCODE_MASK | 0x107u, MEDIA_RECORD = SCANCODE_MASK | 0x108u,
    MEDIA_FAST_FORWARD = SCANCODE_MASK | 0x109u, MEDIA_REWIND = SCANCODE_MASK | 0x10Au, MEDIA_NEXT_TRACK = SCANCODE_MASK | 0x10Bu,
    MEDIA_PREVIOUS_TRACK = SCANCODE_MASK | 0x10Cu, MEDIA_STOP = SCANCODE_MASK | 0x10Du, MEDIA_EJECT = SCANCODE_MASK | 0x10Eu,
    MEDIA_PLAY_PAUSE = SCANCODE_MASK | 0x10Fu, MEDIA_SELECT = SCANCODE_MASK | 0x110u,

    AC_NEW = SCANCODE_MASK | 0x111u, AC_OPEN = SCANCODE_MASK | 0x112u, AC_CLOSE = SCANCODE_MASK | 0x113u,
    AC_EXIT = SCANCODE_MASK | 0x114u, AC_SAVE = SCANCODE_MASK | 0x115u, AC_PRINT = SCANCODE_MASK | 0x116u,
    AC_PROPERTIES = SCANCODE_MASK | 0x117u, AC_SEARCH = SCANCODE_MASK | 0x118u, AC_HOME = SCANCODE_MASK | 0x119u,
    AC_BACK = SCANCODE_MASK | 0x11Au, AC_FORWARD = SCANCODE_MASK | 0x11Bu, AC_STOP = SCANCODE_MASK | 0x11Cu,
    AC_REFRESH = SCANCODE_MASK | 0x11Du, AC_BOOKMARKS = SCANCODE_MASK | 0x11Eu,

    SOFTLEFT = SCANCODE_MASK | 0x11Fu, SOFTRIGHT = SCANCODE_MASK | 0x120u,
    CALL = SCANCODE_MASK | 0x121u, ENDCALL = SCANCODE_MASK | 0x122u,

    LEFT_TAB = EXTENDED_MASK | 0x1u, LEVEL5_SHIFT = EXTENDED_MASK | 0x2u,
    MULTI_KEY_COMPOSE = EXTENDED_MASK | 0x3u,
    META_L = EXTENDED_MASK | 0x4u, META_R = EXTENDED_MASK | 0x5u,
    HYPER_L = EXTENDED_MASK | 0x6u, HYPER_R = EXTENDED_MASK | 0x7u,

    COUNT = 536'870'920
};




using KeyModValueT = enum_t<KeyMod>;
using KeyValueT = enum_t<Key>;
using KeycodeValueT = enum_t<Keycode>;



//  KeyMod methods  //
GEN_BITOPS(KeyMod, KeyModValueT);  // wrapped to a macro now

constexpr bool operator== (const KeyMod first, const KeyMod second) {
    return CAST<KeyModValueT>(first) == CAST<KeyModValueT>(second);
}


constexpr bool filterMods(KeyMod source, KeyMod has, KeyMod has_not=KeyMod::NONE) noexcept {
    return bool(source & has) && (source & has_not)==KeyMod::NONE;
}


// Key/KeyCode methods
template<KeyValueT in>  // this is a c++14 template variable if you are a boomer
constexpr KeycodeValueT keyToKeycode = in | (KeycodeValueT)Keycode::SCANCODE_MASK;



NAMESPACE_END(vexa)
