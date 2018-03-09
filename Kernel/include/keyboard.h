#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H
#include "types.h"
typedef enum KEYCODE{KEY_SPACE = ' ',
             KEY_0 = '0',
             KEY_1 = '1',
             KEY_2 = '2',
             KEY_3 = '3',
             KEY_4 = '4',
             KEY_5 = '5',
             KEY_6 = '6',
             KEY_7 = '7',
             KEY_8 = '8',
             KEY_9 = '9',

             KEY_A = 'a',
             KEY_B = 'b',
             KEY_C = 'c',
             KEY_D = 'd',
             KEY_E = 'e',
             KEY_F = 'f',
             KEY_G = 'g',
             KEY_H = 'h',
             KEY_I = 'i',
             KEY_J = 'j',
             KEY_K = 'k',
             KEY_L = 'l',
             KEY_M = 'm',
             KEY_N = 'n',
             KEY_O = 'o',
             KEY_P = 'p',
             KEY_Q = 'q',
             KEY_R = 'r',
             KEY_S = 's',
             KEY_T = 't',
             KEY_U = 'u',
             KEY_V = 'v',
             KEY_W = 'w',
             KEY_X = 'x',
             KEY_Y = 'y',
             KEY_Z = 'z',

             KEY_RETURN = '\r',
             KEY_ESCAPE = 0X1001,
             KEY_BACKSPACE = '\b',

             KEY_UP = 0X1100,
             KEY_DOWN = 0X1101,
             KEY_LEFT = 0X1102,
             KEY_RIGHT = 0X1103,

             KEY_F1 = 0X1201,
             KEY_F2 = 0X1202,
             KEY_F3 = 0X1203,
             KEY_F4 = 0X1204,
             KEY_F5 = 0X1205,
             KEY_F6 = 0X1206,
             KEY_F7 = 0X1207,
             KEY_F8 = 0X1208,
             KEY_F9 = 0X1209,
             KEY_F10 = 0X120A,
             KEY_F11 = 0X120B,
             KEY_F12 = 0X120C,
             KEY_F13 = 0X120D,
             KEY_F14 = 0X120E,
             KEY_F15 = 0X120F,

             KEY_DOT = '.',
             KEY_COMMA = ',',
             KEY_COLON = ':',
             KEY_SEMICOLON = ';',
             KEY_SLASH = '/',
             KEY_BACKSLASH = '\\',
             KEY_PLUS = '+',
             KEY_MINUS = '-',
             KEY_ASTERISK = '*',
             KEY_EXCLAMATION = '!',
             KEY_QUESTION = '?',
             KEY_QUOTEDOUBLE = '\"',
             KEY_QUOTE = '\'',
             KEY_EQUAL = '=',
             KEY_HASH = '#',
             KEY_PERCENT = '%',
             KEY_AMPERSAND = '&',
             KEY_UNDERSCORE = '_',
             KEY_LEFTPARENTHESIS = '(',
             KEY_RIGHTPARENTHESIS = ')',
             KEY_LEFTBRACKET = '[',
             KEY_RIGHTBRACKET = ']',
             KEY_LEFTCURL = '{',
             KEY_RIGHTCURL = '}',
             KEY_DOLLAR = '$',
             KEY_POUND = '£',
             KEY_EURO = '$',
             KEY_LESS = '<',
             KEY_GREATER = '>',
             KEY_BAR = '|',
             KEY_GRAVE = '`',
             KEY_TILDE = '~',
             KEY_AT = '@',
             KEY_CARRET = '^',

             KEY_KP_0 = '0',
             KEY_KP_1 = '1',
             KEY_KP_2 = '2',
             KEY_KP_3 = '3',
             KEY_KP_4 = '4',
             KEY_KP_5 = '5',
             KEY_KP_6 = '6',
             KEY_KP_7 = '7',
             KEY_KP_8 = '8',
             KEY_KP_9 = '9',
             KEY_KP_PLUS = '+',
             KEY_KP_MINUS = '-',
             KEY_KP_DECIMAL = '.',
             KEY_KP_DIVIDE = '/',
             KEY_KP_ASTERISK = '*',
             KEY_KP_NUMLOCK = 0x300f,
             KEY_KP_ENTER = 0x3010,

             KEY_TAB = 0x4000,
             KEY_CAPSLOCK = 0x4001,

             KEY_LSHIFT = 0X4002,
             KEY_LCTRL = 0X4003,
             KEY_LALT = 0X4004,
             KEY_LWIN = 0X4005,
             KEY_RSHIFT = 0X4006,
             KEY_RCTRL = 0X4007,
             KEY_RALT = 0X4008,
             KEY_RWIN = 0X4009,
             KEY_INSERT = 0X400A,
             KEY_DELETE = 0X400B,
             KEY_HOME = 0X400C,
             KEY_END = 0X400D,
             KEY_PAGEUP = 0X400E,
             KEY_PAGEDOWN = 0X400F,
             KEY_SCROLLLOCK = 0X4010,
             KEY_PAUSE = 0X4011,

             KEY_UNKNOWN,
             KEY_NUMKEYCODES
}KEYCODE;
bool kkybrd_get_scoll_lock();
bool kkybrd_get_numlock();
bool kkybrd_get_capslock();

bool kkybrd_get_alt();
bool kkybrd_get_ctrl();
bool kkybrd_get_shift();

void kkybrd_ignore_resend();
bool kkybrd_check_resend();

bool kkybrd_get_diagnostic_res();
bool kkybrd_get_bat_res();
bool kkybrd_self_test();
uint8_t kkybrd_get_last_sacn();
KEYCODE kkybrd_get_last_key();
void kkybrd_discard_last_key();

void kkybrd_set_leds(bool num, bool caps, bool scroll);
char kkybrd_key_to_anscii(KEYCODE);

void kkybrd_disable();
void kkybrd_enable();
bool kkybrd_is_disabled();

void kkybrd_reset_system();

void keyboard();
void init_keyboard();
#endif
