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
    {DV_Y, X2HEX(X_Y), X2HEX(X_Y), 1, 2}, {DV_Y, X2HEX(X_Y), X2HEX(X_Y), 40, 40},
    // n を y にする
    {DV_F, X2HEX(X_F), X2HEX(X_F), 1, 2}, {DV_F, X2HEX(X_F), X2HEX(X_F), 36, 36},
    {DV_G, X2HEX(X_G), X2HEX(X_G), 1, 2}, {DV_G, X2HEX(X_G), X2HEX(X_G), 34, 34},
    {DV_C, X2HEX(X_C), X2HEX(X_K), 1, 2}, {DV_C, X2HEX(X_C), X2HEX(X_K), 32, 32},
    {DV_D, X2HEX(X_D), X2HEX(X_D), 1, 2}, {DV_D, X2HEX(X_D), X2HEX(X_D), 30, 30},
    {DV_H, X2HEX(X_H), X2HEX(X_H), 1, 2}, {DV_H, X2HEX(X_H), X2HEX(X_H), 28, 28},
    {DV_T, X2HEX(X_T), X2HEX(X_T), 1, 2}, {DV_T, X2HEX(X_T), X2HEX(X_T), 26, 26},
    {DV_B, X2HEX(X_B), X2HEX(X_B), 1, 2}, {DV_B, X2HEX(X_B), X2HEX(X_B), 24, 24},
    {DV_M, X2HEX(X_M), X2HEX(X_M), 1, 2}, {DV_M, X2HEX(X_M), X2HEX(X_M), 22, 22},
    // h を y にする
    {DV_P, X2HEX(X_P), X2HEX(X_P), 1, 2}, {DV_P, X2HEX(X_P), X2HEX(X_P), 21, 21},
    {DV_R, X2HEX(X_R), X2HEX(X_R), 1, 2}, {DV_R, X2HEX(X_R), X2HEX(X_R), 19, 19},
    {DV_L, X2HEX(X_L), X2HEX(X_L), 1, 2}, {DV_L, X2HEX(X_L), X2HEX(X_L), 17, 17},
    {DV_N, X2HEX(X_N), X2HEX(X_N), 16, 1},
    {DV_S, X2HEX(X_S), X2HEX(X_S), 1, 2}, {DV_S, X2HEX(X_S), X2HEX(X_S), 14, 14},
    {DV_Q, X2HEX(X_Q), X2HEX(X_Q), 1, 2}, {DV_Q, X2HEX(X_Q), X2HEX(X_Q), 12, 12},
    {DV_J, X2HEX(X_J), X2HEX(X_J), 1, 2}, {DV_J, X2HEX(X_J), X2HEX(X_J), 10, 10},
    {DV_X, X2HEX(X_X), X2HEX(X_X), 1, 2}, {DV_X, X2HEX(X_X), X2HEX(X_X), 8, 8},
    {DV_W, X2HEX(X_W), X2HEX(X_W), 1, 2}, {DV_W, X2HEX(X_W), X2HEX(X_W), 6, 6},
    {DV_V, X2HEX(X_V), X2HEX(X_V), 1, 2}, {DV_V, X2HEX(X_V), X2HEX(X_V), 4, 4},
    {DV_Z, X2HEX(X_Z), X2HEX(X_Z), 1, 0}, {DV_Z, X2HEX(X_Z), X2HEX(X_Z), 2, 2},
    {DV_N, X2HEX(X_N), X2HEX(X_Y), 2, 2},
    {DV_H, X2HEX(X_H), X2HEX(X_Y), 1, 1},
    {DV_A, X2HEX(X_A), X2HEX(X_A), 0, 1}, {DV_I, X2HEX(X_I), X2HEX(X_I), 0, 1}, {DV_U, X2HEX(X_U), X2HEX(X_U), 0, 1}, {DV_E, X2HEX(X_E), X2HEX(X_E), 0, 1}, {DV_O, X2HEX(X_O), X2HEX(X_O), 0, 1},
    // 二重母音拡張と撥音拡張
    {DV_QUOT, X2HEX(X_I), X2HEX(X_A), 0xff, 1},
    {DV_COMM, X2HEX(X_U), X2HEX(X_O), 0xff, 1},
    {DV_DOT, X2HEX(X_I), X2HEX(X_E), 0xff, 1},
    {DV_SCLN, X2HEX(X_N), X2HEX(X_A), 0xff, 1},
    {DV_Q, X2HEX(X_N), X2HEX(X_O), 0xff, 1}, 
    {DV_J, X2HEX(X_N), X2HEX(X_E), 0xff, 1},
    {DV_K, X2HEX(X_N), X2HEX(X_U), 0xff, 1},
    {DV_X, X2HEX(X_N), X2HEX(X_I), 0xff, 0}
};

static bool enabled_dvorakjp = false;
const static uint8_t SS_DELAY_MAX = 255;
const static uint8_t SS_DELAY_MIN = 0;
const static uint8_t SS_DELAY_ADD = 5;

static uint8_t ss_delay = 0; // send_stringのdelay値

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

uint8_t lengthen_ss_delay(void)
{
    if (ss_delay <= SS_DELAY_MAX - SS_DELAY_ADD) {
        ss_delay += SS_DELAY_ADD;
    }
    uprintf("l %d\n", ss_delay);
    return ss_delay;
}

uint8_t shorten_ss_delay(void)
{
    if (ss_delay >= SS_DELAY_MIN + SS_DELAY_ADD) {
        ss_delay -= SS_DELAY_ADD;
    }
    uprintf("s %d\n", ss_delay);
    return ss_delay;
}

void send_string_with_tapping_term(const char *str, uint8_t tapping_term)
{
    char ss[13] = "";
    char c = *str;
    while (c) {
        if (tapping_term > 0) {
           sprintf(ss, "\1\2%c\1\4%d|\1\3%c", c, TAPPING_TERM + tapping_term, c);
        } else {
           sprintf(ss, "\1\1%c", c);
        }
        send_string(ss);
        c = *(++str);
    }
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
                if (current->raw == X2HEX(X_N)) {
                    djp_stack[djp_count++] = current->raw;
                }
                djp_stack[djp_count] = '\0';
            }
            send_string_with_tapping_term(djp_stack, ss_delay);
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
        send_string_with_tapping_term(raw_stack, ss_delay);
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
