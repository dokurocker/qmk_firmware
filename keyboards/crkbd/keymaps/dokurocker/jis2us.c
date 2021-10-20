#include "jis2us.h"

const key_override_t ** key_overrides = NULL;

void jis2us(layer_state_t layers)
{
    static key_override_t ko_at;
    static key_override_t ko_circ;
    static key_override_t ko_ampr;
    static key_override_t ko_astr;
    static key_override_t ko_lprn;
    static key_override_t ko_rprn;
    static key_override_t ko_unds;
    static key_override_t ko_eql;
    static key_override_t ko_plus;
    static key_override_t ko_lbrc;
    static key_override_t ko_rbrc;
    static key_override_t ko_coln;
    static key_override_t ko_quot;
    static key_override_t ko_dqt;
    static key_override_t ko_grv;
    static key_override_t ko_tild;

    static key_override_t * _key_overrides[] = {
        &ko_at, &ko_circ, &ko_ampr, &ko_astr, &ko_lprn,
        &ko_rprn, &ko_unds, &ko_eql, &ko_plus, &ko_lbrc,
        &ko_rbrc, &ko_coln, &ko_quot, &ko_dqt, &ko_grv,
        &ko_tild, NULL
    };

    // // shift + 2 -> @
    ko_at = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_LBRACKET);
    // shift + 6 -> ^
    ko_circ = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_EQUAL);
    // shift + 7 -> &
    ko_ampr = ko_make_basic(MOD_MASK_SHIFT, KC_7, S(KC_6));
    // shift + 8 -> *
    ko_astr = ko_make_basic(MOD_MASK_SHIFT, KC_8, S(KC_QUOTE));
    // shift + 9 -> (
    ko_lprn = ko_make_basic(MOD_MASK_SHIFT, KC_9, S(KC_8));
    // shift + 0 -> )
    ko_rprn = ko_make_basic(MOD_MASK_SHIFT, KC_0, S(KC_9));
    // shift + - -> _
    ko_unds = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, S(KC_INT1));
    // =
    ko_eql = ko_make_with_layers_and_negmods(0, KC_EQUAL, S(KC_MINUS), layers, (uint8_t)MOD_MASK_SHIFT);
    // shift + = -> +
    ko_plus = ko_make_basic(MOD_MASK_SHIFT, KC_EQUAL, S(KC_SCOLON));
    // [, {
    ko_lbrc = ko_make_with_layers(0, KC_LBRACKET, KC_RBRACKET, layers);
    // ], }
    ko_rbrc = ko_make_basic(0, KC_RBRACKET, KC_NONUS_HASH);
    // :
    ko_coln = ko_make_basic(MOD_MASK_SHIFT, KC_SCOLON, KC_QUOTE);
    // '
    ko_quot = ko_make_with_layers_and_negmods(0, KC_QUOT, S(KC_7), ~0, (uint8_t)MOD_MASK_SHIFT);
    // "
    ko_dqt = ko_make_basic(MOD_MASK_SHIFT, KC_QUOT, S(KC_2));
    // `
    ko_grv = ko_make_with_layers_and_negmods(0, KC_GRAVE, S(KC_LBRACKET), ~0, (uint8_t)MOD_MASK_SHIFT);
    // ~
    ko_tild = ko_make_basic(MOD_MASK_SHIFT, KC_GRAVE, S(KC_EQUAL));
    key_overrides = (const key_override_t **)_key_overrides;
}

typedef struct {
    uint16_t us_keycode; // US配列でのキーコード
    bool needs_shift; // shiftキー必要かどうか
} jis2us_key;

typedef struct {
    bool pressed; // 押されている状態かどうか
    jis2us_key key; // 変換後のキー
    jis2us_key shifted_key; // シフト押下時のキー
} jis2us_key_info;

static void set_jis2us_key_info(jis2us_key_info *info, uint16_t a, bool a_s, uint16_t b, bool b_s)
{
    info->key.us_keycode = a;
    info->key.needs_shift = a_s;
    info->shifted_key.us_keycode = b;
    info->shifted_key.needs_shift = b_s;
}

static bool disabled_backslash = false;

void toggle_bs2yen(void)
{
    disabled_backslash = !disabled_backslash;
}

// shift + 長押しの挙動
//   shiftを離す : shiftを押していない状態の長押しに変わる
// 長押し後にshiftを押す
//   押していたキーはキャンセルされる
// 2(@) : shiftが他のキー（他 6 等）
// 7(&) : shiftが他のキーのshift（他 8 等）
// =(+) : 他のキーのshift、shiftも他のキーのshift（他 ` 等）

static void register_jis2us(jis2us_key_info *info, bool pressed, uint8_t mods)
{
    static uint16_t registered_key = XXXXXXX;
    static bool registered_key_needs_shift = false;

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
            registered_key = info->shifted_key.us_keycode;
            registered_key_needs_shift = false;
        } else {
            if (info->key.needs_shift) {
                register_code16(S(info->key.us_keycode));
            } else {
                register_code(info->key.us_keycode);
            }
            registered_key = info->key.us_keycode;
            registered_key_needs_shift = info->key.needs_shift;
        }
        info->pressed = true;
    } else {
        if (registered_key_needs_shift) {
            unregister_code16(S(registered_key));
        } else {
            unregister_code(registered_key);
        }
        info->pressed = false;
    }
}

bool input_jis2us(uint16_t keycode, bool pressed)
{
    static jis2us_key_info current_jis2us_key_info = {
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

    switch (keycode)
    {
        case KC_LSFT:
        case KC_RSFT:
            if (pressed) {
                mods |= MOD_BIT(keycode); 
                if (current_jis2us_key_info.pressed
                    && ~mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))
                ) {
                    // JIS -> US変換中（shiftキー離した状態）でshiftを押されたら、離す
                    register_jis2us(&current_jis2us_key_info, false, mods);
                }
            } else {
                mods &= ~MOD_BIT(keycode);
                if (!current_jis2us_key_info.pressed) {
                    // 変換対象が押されていない
                    return true;
                }
                if (!mods) {
                    // シフトを全て離した
                    return true;
                }
                // 現在JISキーをUSキーに変換中
                // シフトキーが離されて
                // その結果、シフトキーオフ状態になる
                if (current_jis2us_key_info.shifted_key.needs_shift) {
                    unregister_code(keycode); // シフトキーを離した状態にする
                }
                unregister_code(current_jis2us_key_info.shifted_key.us_keycode);
                current_jis2us_key_info.pressed = false;
                return false;
            }
            return true;
        case JU_BSLS:
            set_jis2us_key_info(&current_jis2us_key_info, disabled_backslash ? KC_INT3 : KC_INT1, false, KC_INT3, true);
            register_jis2us(&current_jis2us_key_info, pressed, mods);
            return true;
        default:
            return true;
    }
    return true;
}
