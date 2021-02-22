#include "jis2us.h"

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

static void set_jis2us_key_info(jis2us_key_info *info, uint16_t a, bool a_s, uint16_t b, bool b_s)
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

static void register_jis2us(jis2us_key_info *info, bool pressed, uint8_t mods)
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
