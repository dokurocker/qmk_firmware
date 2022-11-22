#include "dvorak.h"
#include "dvorakjp/dvorakjp.h"

// enum dvorak_keycodesの最小値（KC_1）を 0 としたqwertyとのマップ配列
static uint16_t d2q_map[][2] = {
    {KC_1, KC_1}, {KC_2, KC_2}, {KC_3, KC_3}, {KC_4, KC_4}, {KC_5, KC_5}, {KC_6, KC_6}, {KC_7, KC_7}, {KC_8, KC_8}, {KC_9, KC_9}, {KC_0, KC_0}, {KC_LBRC, KC_MINS}, {KC_RBRC, KC_EQL},
    {KC_QUOT, KC_Q}, {KC_COMM, KC_W}, {KC_DOT, KC_E}, {KC_P, KC_R}, {KC_Y, KC_T}, {KC_F, KC_Y}, {KC_G, KC_U}, {KC_C, KC_I}, {KC_R, KC_O}, {KC_L, KC_P}, {KC_SLSH, KC_LBRC}, {KC_EQL, KC_RBRC},
    {KC_A, KC_A}, {KC_O, KC_S}, {KC_E, KC_D}, {KC_U, KC_F}, {KC_I, KC_G}, {KC_D, KC_H}, {KC_H, KC_J}, {KC_T, KC_K}, {KC_N, KC_L}, {KC_S, KC_SCLN}, {KC_MINS, KC_QUOT},
    {KC_SCLN, KC_Z}, {KC_Q, KC_X}, {KC_J, KC_C}, {KC_K, KC_V}, {KC_X, KC_B}, {KC_B, KC_N}, {KC_M, KC_M}, {KC_W, KC_COMM}, {KC_V, KC_DOT}, {KC_Z, KC_SLSH}
};

void change_d2q_key(uint16_t d, uint16_t q, bool mods)
{
    d2q_map[d - DV_1][mods ? 1 : 0] = q;
}

static bool enabled_dvorakjp = false;
const static uint8_t TT_MAX = 255;
const static uint8_t TT_MIN = 0;
const static uint8_t TT_ADD = 5;

static uint8_t tapping_term = 0; // send_stringのdelay値

bool is_dvorakjp(void)
{
    return enabled_dvorakjp;
}

void switch_dvorakjp(bool on)
{
    enabled_dvorakjp = on;
}

void toggle_dvorakjp(void)
{
    enabled_dvorakjp = !enabled_dvorakjp;
}

uint8_t lengthen_tapping_term(void)
{
    if (tapping_term <= TT_MAX - TT_ADD) {
        tapping_term += TT_ADD;
    }
    uprintf("l %d\n", tapping_term);
    return tapping_term;
}

uint8_t shorten_tapping_term(void)
{
    if (tapping_term >= TT_MIN + TT_ADD) {
        tapping_term -= TT_ADD;
    }
    uprintf("s %d\n", tapping_term);
    return tapping_term;
}

bool input_dvorak(uint16_t* keycode, bool pressed)
{
    switch(*keycode) {
        case KC_LCTL:
        case KC_RCTL:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_RGUI:
            // TODO: DVキーリセット
            // break;
            return true;
        default:
            break;
    }
 
    if (*keycode < DV_1 || DV_Z < *keycode) {
        return true;
    }
    if (enabled_dvorakjp && pressed && dvorakjp(*keycode, tapping_term)) {
        return false;
    }
    // shiftのみはdvorak配列
    bool mods = (keyboard_report->mods & ~(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) != 0x0;
    uint16_t key = d2q_map[*keycode - DV_1][mods ? 1 : 0];
    static uint16_t pressed_custum_key = XXXXXXX;
    if (pressed) {
        pressed_custum_key = key;
    } else if (pressed_custum_key != XXXXXXX && pressed_custum_key != key) {
        // 先にmodsキーを離している
        key = pressed_custum_key;
    }
    if (key >= ORG_SAFE_RANGE) {
        // カスタマイズしたキーが設定されていたら、キーコードを変更し、後続の処理に任せる
        *keycode = key;
        return true;
    }
    if (pressed) {
        register_code(key);
    } else {
        unregister_code(key);
    }
    return true;
}
