/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Tap Dance support
#ifdef TAP_DANCE_ENABLE
#include "process_tap_dance.h"
#endif

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOVEMENT,
  _FUNCTION
};

enum planck_keycodes {
  BACKLIT = SAFE_RANGE
};

#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_A_ALT,
    TD_S_CTL,
    TD_D_GUI,
    TD_F_SFT,
    TD_J_SFT,
    TD_K_GUI,
    TD_L_CTL,
    TD_SCLN_ALT
};

// Tap Dance definitions - simple double tap to repeat
tap_dance_action_t tap_dance_actions[] = {
    [TD_A_ALT]    = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_A),
    [TD_S_CTL]    = ACTION_TAP_DANCE_DOUBLE(KC_S, KC_S),
    [TD_D_GUI]    = ACTION_TAP_DANCE_DOUBLE(KC_D, KC_D),
    [TD_F_SFT]    = ACTION_TAP_DANCE_DOUBLE(KC_F, KC_F),
    [TD_J_SFT]    = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_J),
    [TD_K_GUI]    = ACTION_TAP_DANCE_DOUBLE(KC_K, KC_K),
    [TD_L_CTL]    = ACTION_TAP_DANCE_DOUBLE(KC_L, KC_L),
    [TD_SCLN_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_SCLN)
};
#endif

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty with Home Row Mods (ACGS) + Tap Dance
 * Left:  A=Alt, S=Ctrl, D=GUI, F=Shift
 * Right: J=Shift, K=GUI, L=Ctrl, ;=Alt
 * G-hold activates movement/navigation layer
 * Double-tap any home row mod key to repeat the letter
 * 
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | A/Alt| S/Ctl| D/GUI| F/Sft| G/Mov|   H  | J/Sft| K/GUI| L/Ctl| ;/Alt|  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sft/En|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | F/LED| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Bksp |  Alt | Ctrl | GUI  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,                 KC_Q,                      KC_W,                      KC_E,                      KC_R,                      KC_T,              KC_Y,    KC_U,                      KC_I,                      KC_O,                      KC_P,                          KC_BSPC,
    KC_ESC,                 MT(MOD_LALT,TD(TD_A_ALT)), MT(MOD_LCTL,TD(TD_S_CTL)), MT(MOD_LGUI,TD(TD_D_GUI)), MT(MOD_LSFT,TD(TD_F_SFT)), LT(_MOVEMENT,KC_G), KC_H,    MT(MOD_RSFT,TD(TD_J_SFT)), MT(MOD_RGUI,TD(TD_K_GUI)), MT(MOD_RCTL,TD(TD_L_CTL)), MT(MOD_LALT,TD(TD_SCLN_ALT)), KC_QUOT,
    KC_LSFT,                KC_Z,                      KC_X,                      KC_C,                      KC_V,                      KC_B,              KC_N,    KC_M,                      KC_COMM,                   KC_DOT,                    KC_SLSH,                       LSFT_T(KC_ENTER),
    LT(_FUNCTION, BACKLIT), KC_LCTL,                   KC_LALT,                   KC_LGUI,                   LOWER,                     KC_SPC,            KC_SPC,  RAISE,                     KC_BSPC,                   KC_RALT,                   KC_RCTL,                       KC_RGUI
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |   |  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Bksp | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  _______, _______, _______, _______, _______, KC_PIPE, KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, _______, _______, _______, _______, _______, _______, S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_BSPC,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Del  | RAlt | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, _______, _______, _______, _______, _______, _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_RALT, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RGB  |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, UG_TOGG, UG_NEXT, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, KC_DEL ,
    UG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Movement (G-hold Navigation Layer)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      | Esc  | PGDN | PGUP |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Home | End  |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |L word|             |R word|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOVEMENT] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______,        _______, KC_ESC,  KC_PGDN,        KC_PGUP, _______, _______, _______,
    _______, _______, _______, _______, _______,        _______, KC_LEFT, KC_DOWN,        KC_UP,   KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______,        _______, _______, KC_HOME,        KC_END,  _______, _______, _______,
    _______, _______, _______, _______, LALT(KC_LEFT),  _______, _______, LALT(KC_RIGHT), _______, _______, _______, _______
),

/* Function (Bottom-left hold)
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F11 |  F12 |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          gpio_write_pin_low(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          gpio_write_pin_high(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}
