#include "dvorakjp.h"

static roma roma_list[] = {
    {DV_Y, X2HEX(X_Y), X2HEX(X_Y), 1, 2}, {DV_Y, X2HEX(X_Y), X2HEX(X_Y), 50, 50},
    // 単一のN（ん）の後の子音（UNNCO -> UNCOと打てるように）
    {DV_N, X2HEX(X_N), X2HEX(X_N), 1, 15},
    // h を y にする
    {DV_H, X2HEX(X_H), X2HEX(X_Y), 52, 1},
    {DV_A, X2HEX(X_A), X2HEX(X_A), 0, 1}, {DV_I, X2HEX(X_I), X2HEX(X_I), 0, 1}, {DV_U, X2HEX(X_U), X2HEX(X_U), 0, 1}, {DV_E, X2HEX(X_E), X2HEX(X_E), 0, 1}, {DV_O, X2HEX(X_O), X2HEX(X_O), 0, 1},
    // 二重母音拡張と撥音拡張
    {DV_QUOT, X2HEX(X_I), X2HEX(X_A), 0xff, 1},
    {DV_COMM, X2HEX(X_U), X2HEX(X_O), 0xff, 1},
    {DV_DOT, X2HEX(X_I), X2HEX(X_E), 0xff, 1},
    {DV_SCLN, X2HEX(X_N), X2HEX(X_A), 0xff, 1},
    {DV_Q, X2HEX(X_N), X2HEX(X_O), 0xff, 1}, 
    {DV_J, X2HEX(X_N), X2HEX(X_E), 0xff, 1},
    {DV_K, X2HEX(X_N), X2HEX(X_U), 0xff, 1},
    {DV_X, X2HEX(X_N), X2HEX(X_I), 0xff, 1},
    // n を y にする
    {DV_F, X2HEX(X_F), X2HEX(X_F), 1, 2}, {DV_F, X2HEX(X_F), X2HEX(X_F), 36, 36},
    {DV_G, X2HEX(X_G), X2HEX(X_G), 1, 2}, {DV_G, X2HEX(X_G), X2HEX(X_G), 34, 34},
    {DV_C, X2HEX(X_C), X2HEX(X_K), 1, 2}, {DV_C, X2HEX(X_C), X2HEX(X_K), 32, 32},
    {DV_D, X2HEX(X_D), X2HEX(X_D), 1, 2}, {DV_D, X2HEX(X_D), X2HEX(X_D), 3, 30},
    {DV_T, X2HEX(X_T), X2HEX(X_T), 1, 2}, {DV_T, X2HEX(X_T), X2HEX(X_T), 1, 28},
    {DV_H, X2HEX(X_H), X2HEX(X_H), 1, 28},
    {DV_H, X2HEX(X_H), X2HEX(X_H), 1, 2}, {DV_H, X2HEX(X_H), X2HEX(X_H), 25, 25},
    {DV_B, X2HEX(X_B), X2HEX(X_B), 1, 2}, {DV_B, X2HEX(X_B), X2HEX(X_B), 23, 23},
    {DV_M, X2HEX(X_M), X2HEX(X_M), 1, 2}, {DV_M, X2HEX(X_M), X2HEX(X_M), 21, 21},
    // h を y にする
    {DV_P, X2HEX(X_P), X2HEX(X_P), 1, 2}, {DV_P, X2HEX(X_P), X2HEX(X_P), 20, 20},
    {DV_R, X2HEX(X_R), X2HEX(X_R), 1, 2}, {DV_R, X2HEX(X_R), X2HEX(X_R), 18, 18},
    {DV_L, X2HEX(X_L), X2HEX(X_L), 1, 2}, {DV_L, X2HEX(X_L), X2HEX(X_L), 16, 16},
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

static roma* current = roma_list;
static char raw_stack[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};
static unsigned char raw_count = 0;
static char djp_stack[8] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
static unsigned char djp_count = 0;

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

void reset_dvorakjp_variables(void)
{
    current = roma_list;
    raw_count = 0;
    djp_count = 0;
    raw_stack[raw_count] = '\0';
    djp_stack[djp_count] = '\0';
}

bool dvorakjp(uint16_t keycode, uint8_t tapping_term)
{
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
            send_string_with_tapping_term(djp_stack, tapping_term);
            reset_dvorakjp_variables();
            return true;
        }
        if (current->miss == 0) {
            break;
        }
        current = current + current->miss;
    }
    if (raw_count > 0) {
        send_string_with_tapping_term(raw_stack, tapping_term);
    }
    reset_dvorakjp_variables();
    return false;
}
