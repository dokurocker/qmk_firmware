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

#include "keymap.h"
#include "jis2us.h"
#include "gui2alt.h"
#include "dvorak.h"

#define _QWERTY 0
#define _DVORAK 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
    KC_LOWR = SAFE_RANGE,
    KC_RASE,
    KC_QWERTY,
    KC_DVORAK,
    KC_BS_SWI,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  JU_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, JU_SCLN, JU_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
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
      KC_LSFT,C(A(KC_DEL)), KC_F2, KC_F3,   KC_F4,   KC_F5,                       KC_F11,  KC_F12,   KC_F1, XXXXXXX, JU_BSLS, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_DEL, _______, KC_RALT
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
                                          KC_LGUI, _______, KC_BSPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX,KC_BS_SWI,KC_DVORAK,KC_QWERTY,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LSFT, _______,  KC_SPC,     KC_ENT, _______, KC_RSFT
                                      //`--------------------------'  `--------------------------'
  ),

//   ),
  [_DVORAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, DV_QUOT, DV_COMM,  DV_DOT,    DV_P,    DV_Y,                         DV_F,    DV_G,    DV_C,    DV_R,    DV_L, DV_SLSH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    DV_A,    DV_O,    DV_E,    DV_U,    DV_I,                         DV_D,    DV_H,    DV_T,    DV_N,    DV_S, DV_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, DV_SCLN,    DV_Q,    DV_J,    DV_K,    DV_X,                         DV_B,    DV_M,    DV_W,    DV_V,    DV_Z, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_LOWR, KC_SPC,      KC_ENT, KC_RASE, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        // case 1UL << _QWERTY:
        //     oled_write_ln_P(PSTR("Qwerty"), false);
        //     break;
        // case 1UL << _DVORAK:
        //     oled_write_ln_P(PSTR("Dvorak"), false);
        //     break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            if (get_highest_layer(default_layer_state) == _QWERTY) {
                oled_write_ln_P(PSTR("Qwerty"), false);
            } else {
                // dvorak
                oled_write_ln_P(is_dvorakjp() ? PSTR("Dvorak_JP") : PSTR("Dvorak"), false);
            }
            break;
    }
    // バックスラッシュが「￥」になっているかを表示
    oled_write_ln_P(is_bs2yen() ? PSTR("Backslash 2 Yen") : PSTR(""), false);
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
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
}
#endif // OLED_ENABLE

void keyboard_post_init_user(void) {
    change_d2q_key(DV_QUOT, JU_QUOT, false);
    change_d2q_key(DV_MINS, JU_MINS, false);
    change_d2q_key(DV_SCLN, JU_SCLN, false);
}

bool input_zenhankaku(uint16_t keycode, bool pressed) {
    // LOWER,RAISEキーを離したときに全角,半角にするかどうかのフラグ
    static bool want_hankaku = false;
    static bool want_zenkaku = false;

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
        case KC_QWERTY:
            if (pressed) {
                default_layer_set(1UL << _QWERTY);
            }
            break;
        case KC_DVORAK:
            if (pressed) {
                if (default_layer_state & 1UL << _DVORAK) {
                    toggle_dvorakjp();
                } else {
                    default_layer_set(1UL << _DVORAK);
                    switch_dvorakjp(false);
                }
            }
            break;
        case KC_BS_SWI:
            if (pressed) {
                toggle_bs2yen();
            }
            break;
        default:
            return true;
    }
    // LOWER,RAISEともに有効ならADJUST
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
    return false;
}

// DvorakJP時のsend_stringのdelay値変更
bool adjust_dvorakjp_delay(uint16_t keycode, bool pressed)
{
    uint8_t mods = get_mods();
    if (!pressed || keycode != KC_DVORAK) {
        return true;
    }

    if ((mods & MOD_BIT(KC_LSFT)) == MOD_BIT(KC_LSFT)) {
        shorten_ss_delay();
    } else if ((mods & MOD_BIT(KC_RSFT)) == MOD_BIT(KC_RSFT)) {
        lengthen_ss_delay();
    } else {
        return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool ret = true;
  input_zenhankaku(keycode, record->event.pressed);
  ret = adjust_dvorakjp_delay(keycode, record->event.pressed);
  ret = ret && change_layer(keycode, record->event.pressed);
  if (!ret) {
      return false;
  }
  // TODO: ビット演算になってる
  ret = ret & input_gui2alt(keycode, record->event.pressed);
  ret = ret & input_dvorak(&keycode, record->event.pressed);
  ret = ret & input_jis2us(keycode, record->event.pressed);
  return ret;
}
