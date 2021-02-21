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
static uint16_t pressed_gui_keycode = XXXXXXX;
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
                pressed_gui_keycode = XXXXXXX;
                pressed_gui = false;
            }
            return false;
        case KC_TAB: // alt + tab (windows)
        case KC_ENTER: // alt + enter (excel セル内で改行)
            if (pressed_gui_keycode != XXXXXXX && !pressed_gui && pressed) {
                // Alt
                pressed_gui_keycode = pressed_gui_keycode == KC_LGUI ? KC_LALT : KC_RALT;
            }
            // break;
        default:
            if (pressed_gui_keycode != XXXXXXX && !pressed_gui && pressed) {
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
// 押されてる状態で別のキーを押されたら離す
// shift: shiftのみ同時押しは後勝ち？
// shift + 何か押しているとき、ほかのシフト押されたら、離して、今押したのが有効になる
typedef struct {
    uint16_t us_keycode; // US配列でのキーコード
    bool needs_shift; // shiftキー必要かどうか
} jis2us_key;

typedef struct {
    bool pressed; // 押されている状態かどうか
    bool shifted; // shiftを押した状態だったか
    jis2us_key key; // 変換後のキー
    jis2us_key shifted_key; // シフト押下時のキー
} jis2us_key_info;

void set_jis2us_key_info(jis2us_key_info *info, uint16_t a, bool a_s, uint16_t b, bool b_s)
{
    info->key.us_keycode = a;
    info->key.needs_shift = a_s;
    info->shifted_key.us_keycode = b;
    info->shifted_key.needs_shift = b_s;
}

// ・shiftとの長押し
// ・押してるときにshift離されたらどうするか
// ・7 のパターン（shift押した時は違うキーのシフト）
// →7 に戻す
// シフトはオフにして、7を押す

// ・2のパターン（shift押したときは違うキーシフトなし）
// →2に戻す
// シフトはすでにオフ
// 単純に2を押す

// ・=のパターン（シフトは違うキーのシフト、シフトないときは違うキーのシフト月）

// 長押し状態でほかのキー押された
// →シフトを話した時の動作キャンセルして、押下中のキーは強制てきにunregist

void register_jis2us(jis2us_key_info *info, bool pressed, uint8_t mods)
{
    uprintf("%d %d\n", mods, keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));
    if (pressed) {
        if (mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
            if (!info->shifted_key.needs_shift) {
                // シフトキーをオフ
                if (mods & MOD_BIT(KC_LSFT)) {
                    unregister_code(KC_LSFT);
                }
                if (mods & MOD_BIT(KC_RSFT)) {
                    unregister_code(KC_RSFT);
                }
            }
            register_code(info->shifted_key.us_keycode);
            info->shifted = true;
        } else {
            if (info->key.needs_shift) {
                register_code16(S(info->key.us_keycode));
            } else {
                register_code(info->key.us_keycode);
            }
            info->shifted = false;
        }
        info->pressed = true;
    } else {
        if (info->shifted) {
            unregister_code(info->shifted_key.us_keycode);
            if (!info->shifted_key.needs_shift) {
                if (mods & MOD_BIT(KC_LSFT)) {
                    register_code(KC_LSFT);
                }
                if (mods & MOD_BIT(KC_RSFT)) {
                    register_code(KC_RSFT);
                }
            }
        } else {
            if (info->key.needs_shift) {
                unregister_code16(S(info->key.us_keycode));
            } else {
                unregister_code(info->key.us_keycode);
            }
        }
        info->pressed = false;
        info->shifted = false;
    }
}

bool input_jis2us(uint16_t keycode, bool pressed)
{
    static jis2us_key_info current_jis2us_key_info = {
        false,
        false,
        {
            XXXXXXX,
            false,
        },
        {
            XXXXXXX,
            false,
        }
    };
    static uint8_t mods = 0; // keyboard_report->modsとは別に、独自でmodsを持つ
    // bool shifted = false;
    // 2 shift押下時キャンセルが必要
    // 7 shift押下時別のキーにする
    // eql shift押していない時、shift必要
    // 長押しの挙動
    // 先にshiftオフ、shiftを押してない状態で長押し続行
    // 　その後、shift押すとshift以外が離した状態になる
    // 　これは、shift押してなくても同じ
    // これに極限まで近づける
    //shifted = keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

    switch (keycode)
    {
        case KC_LSFT:
        case KC_RSFT:
            if (pressed) {
                mods |= MOD_BIT(keycode); 
            } else {
                mods &= ~MOD_BIT(keycode);
            }
            if (current_jis2us_key_info.pressed
                && current_jis2us_key_info.shifted
                && !pressed
                && ((keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) ^ ~MOD_BIT(keycode))
            ) {
                // 現在JISキーをUSキーに変換中
                // シフトキーが離されて
                // その結果、シフトキーオフ状態になる
                if (current_jis2us_key_info.shifted_key.needs_shift) {
                    unregister_code(keycode); // シフトキーを離した状態にする
                }
                unregister_code(current_jis2us_key_info.shifted_key.us_keycode);
                if (current_jis2us_key_info.key.needs_shift) {
                    register_code16(S(current_jis2us_key_info.key.us_keycode));
                } else {
                    register_code(current_jis2us_key_info.key.us_keycode);
                }
                current_jis2us_key_info.pressed = false;
                current_jis2us_key_info.shifted = false;
                return false;
            }
            return true;
        case JU_2:
            set_jis2us_key_info(&current_jis2us_key_info, KC_2, false, KC_LBRACKET, false);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_6:
            set_jis2us_key_info(&current_jis2us_key_info, KC_6, false, KC_EQUAL, false);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_7:
            set_jis2us_key_info(&current_jis2us_key_info, KC_7, false, KC_6, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_8:
            set_jis2us_key_info(&current_jis2us_key_info, KC_8, false, KC_QUOTE, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_9:
            set_jis2us_key_info(&current_jis2us_key_info, KC_9, false, KC_8, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_0:
            set_jis2us_key_info(&current_jis2us_key_info, KC_0, false, KC_9, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_MINS:
            set_jis2us_key_info(&current_jis2us_key_info, KC_MINUS, false, KC_INT1, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_EQL:
            set_jis2us_key_info(&current_jis2us_key_info, KC_MINUS, true, KC_SCOLON, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_LBRC:
            set_jis2us_key_info(&current_jis2us_key_info, KC_RBRACKET, false, KC_RBRACKET, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_RBRC:
            set_jis2us_key_info(&current_jis2us_key_info, KC_NONUS_HASH, false, KC_NONUS_HASH, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_BSLS:
            set_jis2us_key_info(&current_jis2us_key_info, KC_INT1, false, KC_INT3, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_SCLN:
            set_jis2us_key_info(&current_jis2us_key_info, KC_SCOLON, false, KC_QUOTE, false);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_QUOT:
            set_jis2us_key_info(&current_jis2us_key_info, KC_7, true, KC_2, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        case JU_GRV:
            set_jis2us_key_info(&current_jis2us_key_info, KC_LBRACKET, true, KC_EQUAL, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        default:
            return true;
    }
    return true;
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
