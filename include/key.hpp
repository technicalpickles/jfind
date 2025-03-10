#ifndef KEY_HPP
#define KEY_HPP

#include <string>

enum Key {
    K_NULL = 0,
    K_CTRL_A,
    K_CTRL_B,
    K_CTRL_C,
    K_CTRL_D,
    K_CTRL_E,
    K_CTRL_F,
    K_CTRL_G,
    K_CTRL_H, // also ctrl + backspace (ctrl + del)
    K_TAB,    // CTRL-I is tab
    K_CTRL_J,
    K_CTRL_K,
    K_CTRL_L,
    K_ENTER, // CTRL-M is enter
    K_CTRL_N,
    K_CTRL_O,
    K_CTRL_P,
    K_CTRL_Q,
    K_CTRL_R,
    K_CTRL_S,
    K_CTRL_T,
    K_CTRL_U,
    K_CTRL_V,
    K_CTRL_W,
    K_CTRL_X,
    K_CTRL_Y,
    K_CTRL_Z,

    K_ESCAPE,
    K_FS,
    K_CTRL_CLOSE_BRACKET,
    K_CTRL_BACKSLASH, // sends QUIT signal
    K_CTRL_SLASH,

    K_SPACE,
    K_BANG,
    K_DOUBLE_QUOTE,
    K_HASH,
    K_DOLLAR,
    K_PERCENT,
    K_AMPERSAND,
    K_SINGLE_QUOTE,
    K_OPEN_PAREN,
    K_CLOSE_PAREN,
    K_ASTERISK,
    K_ADD,
    K_COMMA,
    K_DASH,
    K_PERIOD,
    K_SLASH,
    K_ZERO,
    K_ONE,
    K_TWO,
    K_THREE,
    K_FOUR,
    K_FIVE,
    K_SIX,
    K_SEVEN,
    K_EIGHT,
    K_NINE,
    K_COLON,
    K_SEMI_COLON,
    K_ANGLE_LEFT,
    K_EQUALS,
    K_ANGLE_RIGHT,
    K_QUESTION_MARK,
    K_AT_SYMBOL,
    K_A,
    K_B,
    K_C,
    K_D,
    K_E,
    K_F,
    K_G,
    K_H,
    K_I,
    K_J,
    K_K,
    K_L,
    K_M,
    K_N,
    K_O,
    K_P,
    K_Q,
    K_R,
    K_S,
    K_T,
    K_U,
    K_V,
    K_W,
    K_X,
    K_Y,
    K_Z,
    K_OPEN_BRACKET,
    K_BACK_SLASH,
    K_CLOSE_BRACKET,
    K_CARET,
    K_UNDERSCORE,
    K_BACK_TICK,
    K_a,
    K_b,
    K_c,
    K_d,
    K_e,
    K_f,
    K_g,
    K_h,
    K_i,
    K_j,
    K_k,
    K_l,
    K_m,
    K_n,
    K_o,
    K_p,
    K_q,
    K_r,
    K_s,
    K_t,
    K_u,
    K_v,
    K_w,
    K_x,
    K_y,
    K_z,
    K_OPEN_BRACE,
    K_PIPE,
    K_CLOSE_BRACE,
    K_TILDE,
    K_BACKSPACE,

    // skip extended ascii (128 - 255)
    // custom keys begin at 256
    K_UP = 256,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_SHIFT_UP,
    K_SHIFT_DOWN,
    K_SHIFT_LEFT,
    K_SHIFT_RIGHT,
    K_ALT_UP,
    K_ALT_DOWN,
    K_ALT_LEFT,
    K_ALT_RIGHT,
    K_CTRL_UP,
    K_CTRL_DOWN,
    K_CTRL_LEFT,
    K_CTRL_RIGHT,

    K_CTRL_TAB,
    K_CTRL_SHIFT_TAB,

    K_ALT_TAB,
    K_ALT_ENTER,

    K_ALT_SPACE,
    K_ALT_BANG,
    K_ALT_DOUBLE_QUOTE,
    K_ALT_HASH,
    K_ALT_DOLLAR,
    K_ALT_PERCENT,
    K_ALT_AMPERSAND,
    K_ALT_SINGLE_QUOTE,
    K_ALT_OPEN_PAREN,
    K_ALT_CLOSE_PAREN,
    K_ALT_ASTERISK,
    K_ALT_ADD,
    K_ALT_COMMA,
    K_ALT_DASH,
    K_ALT_PERIOD,
    K_ALT_SLASH,
    K_ALT_ZERO,
    K_ALT_ONE,
    K_ALT_TWO,
    K_ALT_THREE,
    K_ALT_FOUR,
    K_ALT_FIVE,
    K_ALT_SIX,
    K_ALT_SEVEN,
    K_ALT_EIGHT,
    K_ALT_NINE,
    K_ALT_COLON,
    K_ALT_SEMI_COLON,
    K_ALT_ANGLE_LEFT,
    K_ALT_EQUALS,
    K_ALT_ANGLE_RIGHT,
    K_ALT_QUESTION_MARK,
    K_ALT_AT_SYMBOL,
    K_ALT_A,
    K_ALT_B,
    K_ALT_C,
    K_ALT_D,
    K_ALT_E,
    K_ALT_F,
    K_ALT_G,
    K_ALT_H,
    K_ALT_I,
    K_ALT_J,
    K_ALT_K,
    K_ALT_L,
    K_ALT_M,
    K_ALT_N,
    K_ALT_O,
    K_ALT_P,
    K_ALT_Q,
    K_ALT_R,
    K_ALT_S,
    K_ALT_T,
    K_ALT_U,
    K_ALT_V,
    K_ALT_W,
    K_ALT_X,
    K_ALT_Y,
    K_ALT_Z,
    K_ALT_OPEN_BRACKET,
    K_ALT_BACK_SLASH,
    K_ALT_CLOSE_BRACKET,
    K_ALT_CARET,
    K_ALT_UNDERSCORE,
    K_ALT_BACK_TICK,
    K_ALT_a,
    K_ALT_b,
    K_ALT_c,
    K_ALT_d,
    K_ALT_e,
    K_ALT_f,
    K_ALT_g,
    K_ALT_h,
    K_ALT_i,
    K_ALT_j,
    K_ALT_k,
    K_ALT_l,
    K_ALT_m,
    K_ALT_n,
    K_ALT_o,
    K_ALT_p,
    K_ALT_q,
    K_ALT_r,
    K_ALT_s,
    K_ALT_t,
    K_ALT_u,
    K_ALT_v,
    K_ALT_w,
    K_ALT_x,
    K_ALT_y,
    K_ALT_z,
    K_ALT_OPEN_BRACE,
    K_ALT_PIPE,
    K_ALT_CLOSE_BRACE,
    K_ALT_TILDE,
    K_ALT_BACKSPACE,

    K_DELETE,

    K_ALT_SHIFT_TAB,

    K_F1,
    K_F2,
    K_F3,
    K_F4,
    K_F5,
    K_F6,
    K_F7,
    K_F8,
    K_F9,
    K_F10,
    K_F11,
    K_F12,

    K_UTF8,
    K_MOUSE,
    K_UNKNOWN,
    K_ERROR
};

std::string getKeyName(Key key);

#endif
