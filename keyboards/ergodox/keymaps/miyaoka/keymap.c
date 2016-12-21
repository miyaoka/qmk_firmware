// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on MAC (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

//Alias
#define C(kc) LCTL(kc)
#define A(kc) LALT(kc)
#define SC(kc) (S(C(kc)))
#define SA(kc) (S(A(kc)))
#define KC_M_WU KC_MS_WH_UP
#define KC_M_WD KC_MS_WH_DOWN
#define KC_M_WL KC_MS_WH_LEFT
#define KC_M_WR KC_MS_WH_RIGHT
#define KC_M_U KC_MS_U
#define KC_M_D KC_MS_D
#define KC_M_L KC_MS_L
#define KC_M_R KC_MS_R
#define KC_M_A0 KC_MS_ACCEL0
#define KC_M_A1 KC_MS_ACCEL1
#define KC_M_A2 KC_MS_ACCEL2
#define KC_M_B1 KC_MS_BTN1
#define KC_M_B2 KC_MS_BTN2
#define KC_M_B3 KC_MS_BTN3
#define LANG_EN M(0)
#define LANG_JA M(1)

//Layers
enum layers {
  L_COMMON = 0,
  L_MAC,
  L_WIN,
  L_QWERTY,
  L_QWDR,
  L_GAME,
  L_GAME2,
  L_SYMB,
  L_NAV, // mouse and cursor
  L_CONF // config
};

enum custom_keycodes {
  //--layers--
  // layouts
  QWERTY = SAFE_RANGE,
  QWDR,
  GAME,

  // momentary layer
  SYMB,
  NAV,
  CONF,
  GAME2,

  // os
  MAC,
  WIN,
};

enum macros {
  T_EISU = 0,
  T_KANA
};

uint16_t hold_timers[MATRIX_ROWS][MATRIX_COLS];

// Fillers to make layering clearer
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1! |   2@ |   3# |   4$ |   5% |      |           |      |   6^ |   7& |   8* |   9( |   0) |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |      |      |      |      |      |  [{  |           |  ]}  |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|  Tab |           |  '"  |------+------+------+------+------+--------|
 * | LShift |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |  \|  |  `~  | -_ /S|                                       | =+ /S|  BS  |  DEL |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      | EISU |------|       |------| KANA   | Enter|
 *                                 |      | /LAlt| LCtrl|       | ESC  | /SYMB  | /NAV |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_COMMON] = KEYMAP(  // layer 0 : default
  // left hand
  KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       _______,
  KC_TAB,     _______,    _______,    _______,    _______,    _______,    KC_LBRC,
  KC_LCTL,    _______,    _______,    _______,    _______,    _______,
  KC_LSFT,    _______,    _______,    _______,    _______,    _______,    KC_TAB,
  _______,    _______,    KC_BSLS,    KC_GRV,     SFT_T(KC_MINS),

              _______,    M(T_EISU),
                          _______,
  _______,    M(T_EISU),    KC_LCTL,


  //righthand
  _______,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
  KC_RBRC,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  KC_QUOT,    _______,    _______,    _______,    _______,    _______,    _______,
                          SFT_T(KC_EQL),    KC_BSPC,    KC_DEL,     _______,    _______,

  _______,    _______,
  _______,
  KC_ESC,     M(T_KANA),    LT(L_NAV,KC_ENT)
),


/* Keymap: Mac
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |ctl F2|      |       |ctl sp| ctl F3 |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|      |------|       |------|        |      |
 *                                 |  Cmd |      | LCtrl|       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
[L_MAC] = KEYMAP(  // layer 0 : default
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

                  C(KC_F2),   _______,
                              _______,
  GUI_T(KC_SPC),  _______,    KC_LCTL,


  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  C(KC_SPC),  C(KC_F3),
  _______,
  _______,    _______,    _______
),

/* Keymap: Windows
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Alt F4|      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Space|      |------|       |------|      |      |
 *                                 | LCtrl|      | Win  |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_WIN] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

              A(KC_F4),   _______,
                          _______,
  CTL_T(KC_SPC),    _______,    KC_LGUI,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap : QWERTY
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,<  |  .>  |  /?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_QWERTY] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       _______,
  _______,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  _______,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       _______,
              KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    _______,
  _______,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),

/* Keymap:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   D  |   R  |   F  |      |           |      |   P  |   K  |   Y  |   L  |  ;:  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   U  |   T  |   G  |------|           |------|   H  |   N  |   I  |   O  |   E  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   B  |   V  |      |           |      |   J  |   M  |  ,<  |  .>  |  /?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_QWDR] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_Q,       KC_W,       KC_D,       KC_R,       KC_F,       _______,
  _______,    KC_A,       KC_S,       KC_U,       KC_T,       KC_G,
  _______,    KC_Z,       KC_X,       KC_C,       KC_B,       KC_V,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_P,       KC_K,       KC_Y,       KC_L,       KC_SCLN,    _______,
              KC_H,       KC_N,       KC_I,       KC_O,       KC_E,       _______,
  _______,    KC_J,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),

/* Keymap: Game
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   1  |   2  |   3  |   4  |   5  |  `~  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  | Enter|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|  Tab |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  F21 |  F22 |  F23 |  F24 | ESC  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |   N  |   M  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Space|      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_GAME] = KEYMAP(
  // left hand
  _______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_GRV,
  _______,    KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_ENT,
  _______,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  _______,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_TAB,
  KC_F21,     KC_F22,     KC_F23,     KC_F24,     KC_ESC,

              KC_N,       KC_M,
                          _______,
  LT(L_GAME2,KC_SPC),     _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),

/* Keymap: Game layer2
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   6  |   7  |   8  |   9  |   0  |   Y  |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|   H  |           |      |------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  | F10  |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_GAME2] = KEYMAP(
  // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_Y,
  _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,
  _______,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_H,
  _______,    _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
              _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
),


/* Keymap: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |  <   |           |   >  |   ^  |   &  |   *  |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   1! |   2@ |   3# |   4$ |   5% |------|           |------|   6^ |   7& |   8* |   9( |   0) |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 */
[L_SYMB] = KEYMAP(
    // left hand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_LT,
  _______,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  KC_GT,      KC_CIRC,    KC_AMPR,    KC_ASTR,    _______,    _______,    _______,
              KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______
),


/* Keymap: Cursor, Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 | ->CNF  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | M_U  |      |      |   (  |           |  )   | Home | PgUp |  Up  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | M_L  | M_D  | M_R  |      |------|           |------| End  | Left | Down | Right|   :  |        |
 * |--------+------+------+------+------+------|SC Tab|           | C Tab|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |  ;:  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | MBtn3| MBtn2|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | MBtn1|      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_NAV] = KEYMAP(
    // left hand
    _______,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,            KC_F11,
    _______,      _______,        _______,        KC_M_U,         _______,        _______,          KC_LPRN,
    _______,      _______,        KC_M_L,         KC_M_D,         KC_M_R,         _______,
    _______,      _______,        _______,        _______,        _______,        _______,          SC(KC_TAB),
    _______,      _______,        _______,        KC_M_B3,        KC_M_B2,

                  _______,        _______,
                                  _______,
    KC_M_B1,      _______,        _______,

    //righthand
    KC_F12,       KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,           MO(L_CONF),
    KC_RPRN,      KC_HOME,        KC_PGUP,        KC_UP,          KC_PGDN,        _______,          _______,
                  KC_END,         KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_COLN,          _______,
    C(KC_TAB),    _______,        _______,        _______,        _______,        KC_SCLN,          _______,
                                  _______,        _______,        _______,        _______,          _______,

    _______,      _______,
    _______,
    _______,      _______,   _______
),


/* Keymap: CONF
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET | Mac  | Win  |      |      |      |      |           |      |      |      |      |      | QWRT |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  DEBUG |      |      |      |      |      |      |           |      |      |      |      |      | QWDR |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      | game |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_CONF] = KEYMAP(
  // left hand
  RESET,      MAC,        WIN,        _______,    _______,    _______,    _______,
  DEBUG,      _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
  _______,    _______,    _______,    _______,    _______,

              _______,    _______,
                          _______,
  _______,    _______,    _______,

  //righthand
  _______,    _______,    _______,    _______,    _______,    QWERTY,     _______,
  _______,    _______,    _______,    _______,    _______,    QWDR,       _______,
              _______,    _______,    _______,    _______,    GAME,       _______,
  _______,    _______,    _______,    _______,    _______,    _______,    _______,
                          _______,    _______,    _______,    _______,    _______,

  _______,    _______,
  _______,
  _______,    _______,    _______
)

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void switch_layer (uint8_t layer, bool on) {
  if (on) {
    layer_on(layer);
  } else {
    layer_off(layer);
  }
};

void type_code(uint8_t keycode){
  register_code (keycode);
  unregister_code (keycode);
};

void set_eisu(void){
  type_code (KC_MHEN);
  type_code (KC_LANG2);
};

void set_kana(void){
  type_code (KC_HENK);
  type_code (KC_LANG1);
};

bool is_tap (keyrecord_t *record) {
  return hold_timers[record->event.key.row][record->event.key.col]
  && timer_elapsed (hold_timers[record->event.key.row][record->event.key.col]) < TAPPING_TERM;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // record pressed timer
  if (record->event.pressed) {
    hold_timers[record->event.key.row][record->event.key.col] = timer_read();
  }

  switch (keycode) {
    //--layers--

    //layout
    case QWERTY:
      if (record->event.pressed) {
        layer_move(L_QWERTY);
      }
      return false;
      break;
    case QWDR:
      if (record->event.pressed) {
        layer_move(L_QWDR);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        layer_move(L_GAME);
      }
      return false;
      break;

    //momentary layer
    case GAME2:
      switch_layer(L_GAME2, record->event.pressed);
      return false;
      break;
    case NAV:
      switch_layer(L_NAV, record->event.pressed);
      return false;
      break;
    case CONF:
      switch_layer(L_CONF, record->event.pressed);
      return false;
      break;

    //os
    case MAC:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<L_MAC);
      }
      return false;
      break;
    case WIN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<L_WIN);
      }
      return false;
      break;
  }
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case T_EISU: {
      if (record->event.pressed) {
        register_mods (MOD_BIT(KC_LALT));
      } else {
        unregister_mods (MOD_BIT(KC_LALT));
        if (is_tap(record)) {
          set_eisu();
        }
      }
      break;
    }
    case T_KANA: {
      if (record->event.pressed) {
        layer_on(L_SYMB);
      } else {
        layer_off(L_SYMB);
        if (is_tap(record)) {
          set_kana();
        }
      }
      break;
    }
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  persistant_default_layer_set(1UL<<L_MAC);
  layer_move(L_QWDR);
};
