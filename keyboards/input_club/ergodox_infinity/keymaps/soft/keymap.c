#include QMK_KEYBOARD_H

// Étienne's Infinity ErgoDox trial keymap — PLAN step 1 (conservative).
//
// Goals for this first iteration:
//   - Plain QWERTY alphas in standard positions (isolate the form-factor
//     variable; keep daily Mac-keyboard switching survivable).
//   - Real modifiers live on the THUMB CLUSTERS (the ErgoDox's selling point):
//     GUI / Alt / Ctrl on the small thumb keys, plus Shift on a big thumb key.
//     Pinky LShift/RShift are kept as a day-1 fallback.
//   - One symbol/nav layer (NAV), held via the LEFT big thumb key:
//     LT(NAV, KC_SPC) — tap for Space, hold for the layer.
//   - NO home-row mods yet — that's PLAN step 2.
//
// The "Corne core" (PLAN's deferred 42-key phase) is the inner 3x6 + 3 thumbs;
// the outer columns, the lower under-row, and the extra thumb keys are the
// ErgoDox-only extras and carry conveniences here.

enum layers {
    BASE, // default QWERTY
    NAV,  // symbols (left hand) + navigation (right hand)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BASE
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | Esc  |           | Del  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  [   |           |  ]   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------| Del  |           | Ent  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  `   |  '   |   \  | Left | Right|                                       | Left | Down |  Up  | Right|  ]   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LGui | LAlt |       | RAlt | RGui |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LCtl |       | RCtl |      |      |
 *                                 | Space| LSft |------|       |------| BkSp | Enter|
 *                                 | /NAV |      | Home |       | End  |      |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(
        // left hand
        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_ESC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_DEL,
        KC_GRV,  KC_QUOT, KC_BSLS, KC_LEFT, KC_RGHT,
                                            KC_LGUI, KC_LALT,
                                                     KC_LCTL,
                            LT(NAV, KC_SPC), KC_LSFT, KC_HOME,
        // right hand
        KC_DEL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RBRC,
        KC_RALT, KC_RGUI,
        KC_RCTL,
        KC_END,  KC_BSPC, KC_ENT
    ),
/* NAV (hold left big thumb)
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   #  |   $  |   %  |      |           |      | PgUp | Home |  Up  | End  |      |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   `  |   -  |   =  |   [  |   ]  |------|           |------| PgDn | Left | Down | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ~  |   _  |   +  |   {  |   }  |      |           |      |      |      |      |      |      |        |
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
[NAV] = LAYOUT_ergodox(
        // left hand — symbols
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
        KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS,
        KC_TRNS, KC_GRV,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
        KC_TRNS, KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,
                                                     KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,
        // right hand — navigation
        KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_F12,
                 KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
};
