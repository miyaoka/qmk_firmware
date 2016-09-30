// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define L_BASE 0 // default layer
#define L_MOUS 1 // mouse and cursor
#define L_MCTL 2 // mission ctrl
#define L_RSET 3 // reest

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |  `~  |           |  =+  |   6  |   7  |   8  |   9  |   0  |   \|   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  (   |           |  )   |   Y  |   U  |   I  |   O  |   P  |   -_   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCtrl  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;:  |   '"   |
 * |--------+------+------+------+------+------|  [{  |           |  ]}  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |  ,<  |  .>  |  /?  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | LAlt | Space|                                       | Ent  |  BS  |      | DEL  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |ctl F2|      |       |ctl sp| ctl F3 |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Cmd  |LShift|------|       |------| KANA   | ->CR |
 *                                 |      |      |      |       | EISU |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[L_BASE] = KEYMAP(  // layer 0 : default
    // left hand
    KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_GRV,
    KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_LPRN,
    KC_LCTL,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_LBRC,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_LALT,    KC_SPC,

                LCTL(KC_F2),KC_TRNS,
                            KC_TRNS,
    KC_LGUI,    KC_LSFT,    KC_TRNS,

    //righthand
    KC_EQL,     KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_BSLS,
    KC_RPRN,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_MINS,
                KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,
    KC_RBRC,    KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_RSFT,
                            KC_ENT,     KC_BSPC,    KC_TRNS,    KC_DEL,     KC_TRNS,

    LCTL(KC_SPC),     LCTL(KC_F3),
    KC_TRNS,
    M(0),       M(1),       MO(L_MOUS)
),

/* Keymap: Mouse Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | MWH_L| M_U  | MWH_R| MWH_D|      |           | Home | Home | PgUp |  Up  | PgDn |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | M_L  | M_D  | M_R  | MWH_U|------|           |------| End  | Left | Down | Right|      |        |
 * |--------+------+------+------+------+------|      |           | End  |------+------+------+------+------+--------|
 * | MAcl1  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      | -> RT|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | MBtn3|      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | MBtn1| MBtn2|------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_MOUS] = KEYMAP(
    // left hand
    KC_TRNS,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,            KC_F11,
    KC_TRNS,      KC_TRNS,        KC_MS_WH_LEFT,  KC_MS_U,        KC_MS_WH_RIGHT, KC_MS_WH_DOWN,    KC_TRNS,
    KC_TRNS,      KC_TRNS,        KC_MS_L,        KC_MS_D,        KC_MS_R,        KC_MS_WH_UP,
    KC_MS_ACCEL1, KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,          KC_TRNS,
    KC_TRNS,      KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,

                  KC_MS_BTN3,     KC_TRNS,
                                  KC_TRNS,
    KC_MS_BTN1,   KC_MS_BTN2,     KC_TRNS,

    //righthand
    KC_F12,     KC_F6,      KC_F7,              KC_F8,            KC_F9,                KC_F10,     KC_TRNS,
    KC_HOME,    KC_HOME,    KC_PGUP,            KC_UP,            KC_PGDN,              KC_TRNS,    KC_TRNS,
                KC_END,     KC_LEFT,            KC_DOWN,          KC_RIGHT,             MO(L_MCTL), KC_TRNS,
    KC_END,     KC_TRNS,    KC_TRNS,            KC_TRNS,          KC_TRNS,              KC_TRNS,    KC_TRNS,
                            KC_TRNS,            KC_TRNS,          KC_TRNS,              KC_TRNS,    MO(L_RSET),

    KC_TRNS,    KC_TRNS,
    KC_TRNS,
    KC_TRNS,    KC_TRNS,   KC_TRNS
),


/* Keymap: Mission Control
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | C Up |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |C Left|C Down|C Righ|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |  RSET|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
/*
[L_MCTL] = KEYMAP(
    // left hand
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                KC_TRNS,    KC_TRNS,
                            KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,

    //righthand
    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_PGUP,    KC_TRNS,        LCTL(KC_UP),    KC_TRNS,        KC_TRNS,    KC_PGUP,
                KC_PGDN,    LCTL(KC_LEFT),  LCTL(KC_DOWN),  LCTL(KC_RIGHT), KC_TRNS,    KC_PGDN,
    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    KC_TRNS,
                            KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    MO(L_RSET),

    KC_TRNS,    KC_TRNS,
    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS
),
*/

/* Keymap: RESET
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  RESET |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_RSET] = KEYMAP(
    // left hand
    RESET,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

                KC_TRNS,    KC_TRNS,
                            KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,

    //righthand
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,

    KC_TRNS,    KC_TRNS,
    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS
)
};

const uint16_t PROGMEM fn_actions[] = {
//    [1] = ACTION_LAYER_TAP_TOGGLE(L1)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO( T(MHEN), T(LANG2), END);
                break;
            case 1:
                return MACRO( T(HENK), T(LANG1), END);
                break;
        }
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
