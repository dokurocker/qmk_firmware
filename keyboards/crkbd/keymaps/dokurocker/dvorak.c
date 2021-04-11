#include "dvorak.h"

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

struct _roma {
    uint16_t keycode;
    char raw;
    char dvorakjp;
    char hit;
    char miss;
};

typedef struct _roma roma;

roma roma_list[] = {
    {DV_Y, 'y', 'y', 1, 2}, {DV_Y, 'y', 'y', 40, 40},
    // n を y にする
    {DV_F, 'f', 'f', 1, 2}, {DV_F, 'f', 'f', 36, 36},
    {DV_G, 'g', 'g', 1, 2}, {DV_G, 'g', 'g', 34, 34},
    {DV_C, 'c', 'k', 1, 2}, {DV_C, 'c', 'k', 32, 32},
    {DV_D, 'd', 'd', 1, 2}, {DV_D, 'd', 'd', 30, 30},
    {DV_H, 'h', 'h', 1, 2}, {DV_H, 'h', 'h', 28, 28},
    {DV_T, 't', 't', 1, 2}, {DV_T, 't', 't', 26, 26},
    {DV_B, 'b', 'b', 1, 2}, {DV_B, 'b', 'b', 24, 24},
    {DV_M, 'm', 'm', 1, 2}, {DV_M, 'm', 'm', 22, 22},
    // h を y にする
    {DV_P, 'p', 'p', 1, 2}, {DV_P, 'p', 'p', 21, 21},
    {DV_R, 'r', 'r', 1, 2}, {DV_R, 'r', 'r', 19, 19},
    {DV_L, 'l', 'l', 1, 2}, {DV_L, 'l', 'l', 17, 17},
    {DV_N, 'n', 'n', 16, 1},
    {DV_S, 's', 's', 1, 2}, {DV_S, 's', 's', 14, 14},
    {DV_Q, 'q', 'q', 1, 2}, {DV_Q, 'q', 'q', 12, 12},
    {DV_J, 'j', 'j', 1, 2}, {DV_J, 'j', 'j', 10, 10},
    {DV_X, 'x', 'x', 1, 2}, {DV_X, 'x', 'x', 8, 8},
    {DV_W, 'w', 'w', 1, 2}, {DV_W, 'w', 'w', 6, 6},
    {DV_V, 'v', 'v', 1, 2}, {DV_V, 'v', 'v', 4, 4},
    {DV_Z, 'z', 'z', 1, 0}, {DV_Z, 'z', 'z', 2, 2},
    {DV_N, 'n', 'y', 2, 2},
    {DV_H, 'h', 'y', 1, 1},
    {DV_A, 'a', 'a', 0, 1}, {DV_I, 'i', 'i', 0, 1}, {DV_U, 'u', 'u', 0, 1}, {DV_E, 'e', 'e', 0, 1}, {DV_O, 'o', 'o', 0, 1},
    // 二重母音拡張と撥音拡張
    {DV_QUOT, 'i', 'a', 0xff, 1},
    {DV_COMM, 'u', 'o', 0xff, 1},
    {DV_DOT, 'i', 'e', 0xff, 1},
    {DV_SCLN, 'n', 'a', 0xff, 1},
    {DV_Q, 'n', 'o', 0xff, 1}, 
    {DV_J, 'n', 'e', 0xff, 1},
    {DV_K, 'n', 'u', 0xff, 1},
    {DV_X, 'n', 'i', 0xff, 0}
};

static bool enabled_dvorakjp = false;

void switch_dvorakjp(bool on)
{
    enabled_dvorakjp = on;
}

void toggle_dvorakjp(void)
{
    enabled_dvorakjp = !enabled_dvorakjp;
}

bool dvorakjp(uint16_t keycode)
{
    static roma* current = roma_list;
    static char raw_stack[5] = {'\0', '\0', '\0', '\0', '\0'};
    static unsigned char raw_count = 0;
    static char djp_stack[7] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    static unsigned char djp_count = 0;
    
    while (1) {
        if (current->keycode == keycode) {
            raw_stack[raw_count++] = current->raw;
            raw_stack[raw_count] = '\0';
            djp_stack[djp_count++] = current->dvorakjp;
            djp_stack[djp_count] = '\0';
            if (current->hit > 0 && current->hit != 0xff) {
                current = current + current->hit;
                return true;
            }
            if (current->hit == 0xff) {
                // 二重母音拡張と撥音拡張
                djp_stack[djp_count++] = current->raw;
                if (current->raw == 'n') {
                    djp_stack[djp_count++] = current->raw;
                }
                djp_stack[djp_count] = '\0';
            }
            send_string(djp_stack);
            raw_count = 0;
            djp_count = 0;
            raw_stack[raw_count] = '\0';
            djp_stack[djp_count] = '\0';
            current = roma_list;
            return true;
        }
        if (current->miss == 0) {
            break;
        }
        current = current + current->miss;
    }
    current = roma_list;
    djp_count = 0;
    djp_stack[djp_count] = '\0';
    if (raw_count > 0) {
        send_string(raw_stack);
        raw_count = 0;
        raw_stack[raw_count] = '\0';
    }
    return false;
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
    if (enabled_dvorakjp && pressed && dvorakjp(*keycode)) {
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
