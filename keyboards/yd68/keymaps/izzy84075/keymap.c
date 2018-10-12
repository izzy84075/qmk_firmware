/* Copyright 2018 Ryan "Izzy" Bales
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

#define _BL 0
#define _FL 1

#define ______ KC_TRNS

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  BT_PWR = SAFE_RANGE,
  RGB_PWR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BL] = LAYOUT_ansi( /* Base */
	KC_ESC,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV,  \
	KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL,  \
	KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT, KC_PGUP, \
	KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,KC_UP,  KC_PGDN, \
	KC_LCTL, KC_LGUI,KC_LALT,                        KC_SPC,                 KC_RALT,MO(_FL),KC_RCTRL,KC_LEFT,KC_DOWN,KC_RGHT \
	),
  [_FL] = LAYOUT_ansi( /* Base */
    ______,  KC_F1 , KC_F2,  KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL, KC_PSCR ,  \
    RGB_PWR, ______, KC_UP,  ______,  ______, RGB_MOD,RGB_VAI,RGB_SAI,RGB_HUI,______, ______, KC_VOLD,KC_VOLU,KC_MUTE,______, \
    RGB_TOG, KC_LEFT,KC_DOWN,KC_RIGHT,______, ______, RGB_VAD,RGB_SAD,RGB_HUD,______, ______, ______,         ______, KC_HOME, \
    ______,          ______, BL_DEC,  BL_TOGG,BL_INC, ______, ______, ______, ______, ______, ______, KC_BTN1,KC_MS_U,KC_END, \
    ______,  ______, ______,                          ______,                 ______, ______, ______, KC_MS_L,KC_MS_D,KC_MS_R \
	),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BT_PWR:
      if (record->event.pressed) {
        // when keycode YD68_BT_PWR is pressed
		    PORTB ^= (1<<2);
        if(!(PORTB&(1<<2))) {
          print("\nBT on\n");
        } else {
          print("\nBT off\n");
        }
      } else {
        // when keycode YD68_BT_PWR is released
      }
      break;
    case RGB_PWR:
      if (record->event.pressed) {
        // when keycode YD68_RGB_PWR is pressed
		    PORTE ^= (1<<2);

        //RGB data output low
        DDRB |= (1<<3);
        PORTB &= ~(1<<3);

        if(!(PORTE&(1<<2))) {
          print("\nRGB on\n");
        } else {
          print("\nRGB off\n");
        }
      } else {
        // when keycode YD68_RGB_PWR is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
