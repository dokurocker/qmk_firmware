/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#define _DEFAULT 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
    KC_LOWR = SAFE_RANGE,
    KC_RASE,
    // JIS配列をUS配列にする
    JU_2,
    JU_6,
    JU_7,
    JU_8,
    JU_9,
    JU_0,
    JU_MINS,
    JU_EQL,
    JU_LBRC,
    JU_RBRC,
    JU_BSLS,
    JU_SCLN,
    JU_QUOT,
    JU_GRV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DEFAULT] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  JU_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, JU_SCLN, JU_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_LOWR, KC_SPC,      KC_ENT, KC_RASE, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    JU_2,    KC_3,    KC_4,    KC_5,                         JU_6,    JU_7,    JU_8,    JU_9,    JU_0,  JU_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, JU_LBRC, JU_RBRC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,C(A(KC_DEL)), KC_F2, KC_F3,   KC_F4,   KC_F5,                       KC_F11,  KC_F12,   KC_F1, XXXXXXX, JU_BSLS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       JU_GRV, KC_EXLM, KC_LBRC, KC_HASH,  KC_DLR, KC_PERC,                       KC_EQL, KC_CIRC, KC_DQUO, KC_ASTR, KC_LPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, C(KC_A), C(KC_S), C(KC_D), C(KC_F), C(KC_G),                      C(KC_H), C(KC_J), C(KC_K), C(KC_L),C(JU_SCLN),KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B),                      C(KC_N), C(KC_M),C(KC_COMM),C(KC_DOT),C(KC_SLSH),KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

// LOWER,RAISEキーを離したときに全角,半角にするかどうかのフラグ
static bool want_hankaku = false;
static bool want_zenkaku = false;

bool input_zenhankaku(uint16_t keycode, bool pressed) {
    switch (keycode) {
        case KC_LOWR:
            if (pressed) {
                if (want_zenkaku) {
                    want_zenkaku = false;
                    return false;
                }
                want_hankaku = true;
            } else {
                if (want_hankaku) {
                    tap_code(KC_MHEN); // macOS の場合は KC_LANG2
                    want_hankaku = false;
                }
            }
            return false;
        case KC_RASE:
            if (pressed) {
                if (want_hankaku) {
                    want_hankaku = false;
                    return false;
                }
                want_zenkaku = true;
            } else {
                if (want_zenkaku) {
                    tap_code(KC_HENK); // macOS の場合は KC_LANG2
                    want_zenkaku = false;
                }
            }
            return false;
        default:
            want_hankaku = false;
            want_zenkaku = false;
            return true;
    }
}

// winキーの動作変更
static uint16_t pressed_gui_keycode = 0;
static bool pressed_gui = false;

bool input_gui(uint16_t keycode, bool pressed) {
    switch (keycode) {
        case KC_LGUI:
        case KC_RGUI:
            if (pressed) {
                pressed_gui_keycode = keycode;
            } else {
                if (pressed_gui) {
                    unregister_code(pressed_gui_keycode);
                } else {
                    tap_code(pressed_gui_keycode);
                }
                pressed_gui_keycode = 0;
                pressed_gui = false;
            }
            return false;
        case KC_TAB: // alt + tab (windows)
        case KC_ENTER: // alt + enter (excel セル内で改行)
            if (pressed_gui_keycode > 0 && !pressed_gui && pressed) {
                // Alt
                pressed_gui_keycode = pressed_gui_keycode == KC_LGUI ? KC_LALT : KC_RALT;
            }
            // break;
        default:
            if (pressed_gui_keycode > 0 && !pressed_gui && pressed) {
                pressed_gui = true;
                register_code(pressed_gui_keycode);
            }
            break;
    }
    return true;
}
// レイヤー変更
bool change_layer(uint16_t keycode, bool pressed) {
    switch (keycode) {
        case KC_LOWR:
            if (pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            break;
        case KC_RASE:
            if (pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            break;
        default:
            return true;
    }
    // LOWER,RAISEともに有効ならADJUST
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
    return false;
}

// JIS配列をUS配列として入力
bool input_jis2us(uint16_t keycode, bool pressed)
{
    bool lshift = false;
    bool rshift = false;
    if (!pressed) {
        return true;
    }
    lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
    rshift = keyboard_report->mods & MOD_BIT(KC_RSFT);
    switch (keycode)
    {
        case JU_2:
            if (lshift || rshift) {
                if (lshift) {
                    unregister_code(KC_LSFT);
                }
                if (rshift) {
                    unregister_code(KC_RSFT);
                }
                tap_code(KC_LBRACKET);
                if (lshift) {
                    register_code(KC_LSFT);
                }
                if (rshift) {
                    register_code(KC_RSFT);
                }
            } else {
                tap_code(KC_2);
            }
            break;
        case JU_6:
            if (lshift || rshift) {
                if (lshift) {
                    unregister_code(KC_LSFT);
                }
                if (rshift) {
                    unregister_code(KC_RSFT);
                }
                tap_code(KC_EQUAL);
                if (lshift) {
                    register_code(KC_LSFT);
                }
                if (rshift) {
                    register_code(KC_RSFT);
                }
            } else {
                tap_code(KC_6);
            }
            break;
        case JU_7:
            if (lshift || rshift) {
                tap_code(KC_6);
            } else {
                tap_code(KC_7);
            }
            break;
        case JU_8:
            if (lshift || rshift) {
                tap_code(KC_QUOTE);
            } else {
                tap_code(KC_8);
            }
            break;
        case JU_9:
            if (lshift || rshift) {
                tap_code(KC_8);
            } else {
                tap_code(KC_9);
            }
            break;
        case JU_0:
            if (lshift || rshift) {
                tap_code(KC_9);
            } else {
                tap_code(KC_0);
            }
            break;
        case JU_MINS:
            if (lshift || rshift) {
                tap_code(KC_INT1);
            } else {
                tap_code(KC_MINUS);
            }
            break;
        case JU_EQL:
            if (lshift || rshift) {
                tap_code(KC_SCOLON);
            } else {
                tap_code16(S(KC_MINUS));
            }
            break;
        case JU_LBRC:
            if (lshift || rshift) {
                tap_code(KC_RBRACKET);
            } else {
                tap_code(KC_RBRACKET);
            }
            break;
        case JU_RBRC:
            if (lshift || rshift) {
                tap_code(KC_NONUS_HASH);
            } else {
                tap_code(KC_NONUS_HASH);
            }
            break;
        case JU_BSLS:
            if (lshift || rshift) {
                tap_code(KC_INT3);
            } else {
                tap_code(KC_INT1);
            }
            break;
        case JU_SCLN:
            if (lshift || rshift) {
                if (lshift) {
                    unregister_code(KC_LSFT);
                }
                if (rshift) {
                    unregister_code(KC_RSFT);
                }
                tap_code(KC_QUOTE);
                if (lshift) {
                    register_code(KC_LSFT);
                }
                if (rshift) {
                    register_code(KC_RSFT);
                }
            } else {
                tap_code(KC_SCOLON);
            }
            break;
        case JU_QUOT:
            if (lshift || rshift) {
                tap_code(KC_2);
            } else {
                tap_code16(S(KC_7));
            }
            break;
        case JU_GRV:
            if (lshift || rshift) {
                tap_code(KC_EQUAL);
            } else {
                tap_code16(S(KC_LBRACKET));
            }
            break;
        default:
            return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool ret = true;
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  ret = input_zenhankaku(keycode, record->event.pressed);
  ret = ret & input_gui(keycode, record->event.pressed);
  ret = ret & change_layer(keycode, record->event.pressed);
  ret = ret & input_jis2us(keycode, record->event.pressed);
  return ret;
}
#endif // OLED_DRIVER_ENABLE
