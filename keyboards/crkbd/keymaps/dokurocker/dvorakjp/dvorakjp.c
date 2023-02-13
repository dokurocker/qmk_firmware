#include "dvorakjp.h"

static roma roma_list[] = {
    {DV_P, X2HEX_EX6(X_P), X2HEX(X_MINUS) - X_MASK, 0, 1},
    {DV_Y, X2HEX_EX6(X_Y), X2HEX(X_SLASH) - X_MASK, 0, 1},
    {DV_K + DV_SHIFT, X2HEX_EX6(X_K), X2HEX(X_GRAVE) - X_MASK, 0, 1},
    {DV_K, X2HEX_EX7(X_N), X2HEX(X_N), 0, 1},
    // f は y に変更
    {DV_F, X2HEX_EX5(X_F), X2HEX(X_Y), 1, 3}, {DV_F, X2HEX_EX5(X_F), X2HEX(X_Y), 1, 1},
    // f,ff の次が n だったら fy,ffy にする(フャ行)
    {DV_N, X2HEX_EX4(X_N), X2HEX(X_Y), 48, 48-4},
    // 単一のN（ん）の後の子音をチェックできるように0xfeで特別な対応（UNNCO -> UNCOと打てるように）
    {DV_N, X2HEX_EX2(X_N), X2HEX(X_N), 47-2, 1},
    // 子音
    // n を y にする
    {DV_G, X2HEX(X_G), X2HEX(X_G), 1, 2}, {DV_G, X2HEX(X_G), X2HEX(X_G), 46-5, 46-5},
    {DV_C, X2HEX(X_C), X2HEX(X_K), 1, 2}, {DV_C, X2HEX(X_C), X2HEX(X_K), 44-5, 44-5},
    {DV_D, X2HEX(X_D), X2HEX(X_D), 1, 2}, {DV_D, X2HEX(X_D), X2HEX(X_D), 42-6, 42-6},
    {DV_T, X2HEX(X_T), X2HEX(X_T), 1, 2}, {DV_T, X2HEX(X_T), X2HEX(X_T), 40-10, 40-10},
    {DV_H, X2HEX_EX3(X_H), X2HEX(X_F), 1, 3}, {DV_H, X2HEX_EX3(X_H), X2HEX(X_F), 1, 1},
    // h,hh の次が w だったら hw,hhw は f,ff にする(ファ行)
    {DV_W, X2HEX_EX4(X_W), X2HEX(X_UNDEF), 37-4, 37-4},

    {DV_B, X2HEX(X_B), X2HEX(X_B), 1, 2}, {DV_B, X2HEX(X_B), X2HEX(X_B), 35-4, 35-4},
    {DV_M, X2HEX(X_M), X2HEX(X_M), 1, 4}, {DV_M, X2HEX(X_M), X2HEX(X_M), 33-4, 33-4},
    // h を y にする
    {DV_P, X2HEX(X_P), X2HEX(X_P), 1, 2}, {DV_P, X2HEX(X_P), X2HEX(X_P), 31-2, 31-2},
    {DV_R, X2HEX(X_R), X2HEX(X_R), 1, 2}, {DV_R, X2HEX(X_R), X2HEX(X_R), 29-2, 29-2},
    {DV_L, X2HEX(X_L), X2HEX(X_P), 1, 2}, {DV_L, X2HEX(X_L), X2HEX(X_P), 27-2, 27-2},
    {DV_S, X2HEX(X_S), X2HEX(X_S), 1, 2}, {DV_S, X2HEX(X_S), X2HEX(X_S), 25-3, 25-3},
    {DV_Q, X2HEX(X_Q), X2HEX(X_Q), 1, 2}, {DV_Q, X2HEX(X_Q), X2HEX(X_Q), 23-3, 23-3},
    {DV_J, X2HEX(X_J), X2HEX(X_J), 1, 2}, {DV_J, X2HEX(X_J), X2HEX(X_J), 21-2, 21-2},
    {DV_K, X2HEX(X_K), X2HEX(X_K), 1, 2}, {DV_K, X2HEX(X_K), X2HEX(X_K), 19-3, 19-3},
    {DV_X, X2HEX(X_X), X2HEX(X_X), 1, 2}, {DV_X, X2HEX(X_X), X2HEX(X_X), 17-9, 17-9},
    {DV_W, X2HEX(X_W), X2HEX(X_W), 1, 2}, {DV_W, X2HEX(X_W), X2HEX(X_W), 15-6, 15-6},
    {DV_V, X2HEX(X_V), X2HEX(X_V), 1, 2}, {DV_V, X2HEX(X_V), X2HEX(X_V), 13-2, 13-2},
    {DV_Z, X2HEX(X_Z), X2HEX(X_Z), 1, 0}, {DV_Z, X2HEX(X_Z), X2HEX(X_Z), 11-3, 11-3},
    // 拗音
    {DV_S, X2HEX(X_S), X2HEX(X_S), 10, 4},  // ツァ行(ts)
    // ヵ,ヶ,っ x[ck](xca xka xce xke) xt(xtu)
    {DV_C, X2HEX(X_C), X2HEX(X_K), 9, 1}, {DV_K, X2HEX(X_K), X2HEX(X_K), 8, 1}, {DV_T, X2HEX(X_T), X2HEX(X_T), 7, 5},
    {DV_H, X2HEX(X_H), X2HEX(X_H), 6, 1}, // テャ,デャ,ウァ行([tdw]h)
    {DV_W, X2HEX(X_W), X2HEX(X_W), 5, 1}, // クァ,グァ,トァ,ドァ[cgtd]w
    {DV_N, X2HEX(X_N), X2HEX(X_Y), 4, 4},
    {DV_W, X2HEX(X_W), X2HEX(X_W), 3, 1}, // クァ,スァ,ズァ,ヮ[kqszx]w(xwa)
    {DV_H, X2HEX(X_H), X2HEX(X_Y), 2, 2},
    {DV_Y, X2HEX(X_Y), X2HEX(X_Y), 1, 1},
    // 母音
    {DV_A, X2HEX(X_A), X2HEX(X_A), 0, 1}, {DV_I, X2HEX(X_I), X2HEX(X_I), 0, 1}, {DV_U, X2HEX(X_U), X2HEX(X_U), 0, 1}, {DV_E, X2HEX(X_E), X2HEX(X_E), 0, 1}, {DV_O, X2HEX(X_O), X2HEX(X_O), 0, 1},
    // 二重母音拡張と撥音拡張
    {DV_QUOT, X2HEX_EX1(X_I), X2HEX(X_A), 0, 1},
    {DV_COMM, X2HEX_EX1(X_U), X2HEX(X_O), 0, 1},
    {DV_DOT, X2HEX_EX1(X_I), X2HEX(X_E), 0, 1},
    {DV_P, X2HEX_EX1(X_U), X2HEX(X_U), 0, 1},
    {DV_Y, X2HEX_EX1(X_I), X2HEX(X_U), 0, 1},
    {DV_SCLN, X2HEX_EX1(X_N), X2HEX(X_A), 0, 1},
    {DV_Q, X2HEX_EX1(X_N), X2HEX(X_O), 0, 1}, 
    {DV_J, X2HEX_EX1(X_N), X2HEX(X_E), 0, 1},
    {DV_K, X2HEX_EX1(X_N), X2HEX(X_U), 0, 1},
    {DV_X, X2HEX_EX1(X_N), X2HEX(X_I), 0, 0}
};
// 単一nでな行チェック
// n なら な行チェックし、な行じゃなければ、次は子音
static roma* next = NULL;
// 前回疑似COMBOキー
static bool is_prev_like_combo_a = false; // コンボ成立でdvorakjp有効
static bool is_prev_like_combo_b = false; // コンボ成立でdvorakjp無効
static roma* current = roma_list;
static char raw_stack[10] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
static unsigned char raw_count = 0;
static char djp_stack[10] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
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
    next = NULL;
    is_prev_like_combo_a = false;
    is_prev_like_combo_b = false;
    raw_count = 0;
    djp_count = 0;
    raw_stack[raw_count] = '\0';
    djp_stack[djp_count] = '\0';
}

bool dvorakjp(uint16_t keycode, uint8_t tapping_term)
{
    while (1) {
#ifndef DOKU_MOCKED
        bool is_shifted = (keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) != 0x0;
#endif
        if (current->keycode == keycode || (current->keycode == keycode + DV_SHIFT && is_shifted)) {
            char raw = current->raw & X_MASK;
            char dvorakjp = current->dvorakjp & X_MASK;
            bool is_vowels_expantion = (current->raw & ~X_MASK) == EX1_BIT;
            bool is_nagyou_possibility = (current->raw & ~X_MASK) == EX2_BIT;
            bool is_like_combo_a = (current->raw & ~X_MASK) == EX3_BIT;
            bool is_like_combo_b = (current->raw & ~X_MASK) == EX5_BIT;
            bool is_like_combo_end = (current->raw & ~X_MASK) == EX4_BIT;
            bool is_symbol = (current->raw & ~X_MASK) == EX6_BIT;
            bool is_k_to_nn = (current->raw & ~X_MASK) == EX7_BIT;
            if (is_symbol) {
                // TODO: Shiftキーは有効になるか、うまく動くかは焼いてみないとわからない
                dvorakjp = dvorakjp + X_MASK;
            }
            if (raw_count > 0 || is_vowels_expantion || raw != dvorakjp || is_like_combo_a || is_like_combo_b || is_k_to_nn) {
                if (is_like_combo_a) {
                    // 疑似コンボ開始
                    is_prev_like_combo_a = true;
                } else if (is_like_combo_b) {
                    // 疑似コンボ開始
                    is_prev_like_combo_b = true;
                } else if (is_prev_like_combo_a && is_like_combo_end) {
                    // 疑似コンボ合致、積んだdvorakで確定
                    is_prev_like_combo_a = false;
                } else if (is_prev_like_combo_b && !is_like_combo_end) {
                    // 疑似コンボ合致せず、積んだdvorakで確定
                    is_prev_like_combo_b = false;
                } else if (is_prev_like_combo_a) {
                    // 疑似コンボ合致せず、これまでの生入力を転記
                    // TODO: 途中までコンボ関係なしに変更してた場合も上書かれてしまう
                    sprintf(djp_stack, "%s", raw_stack);
                    djp_count = raw_count;
                    is_prev_like_combo_a = false;
                } else if (is_prev_like_combo_b && is_like_combo_end) {
                    // 疑似コンボ合致、これまでの生入力を転記
                    // TODO: 途中までコンボ関係なしに変更してた場合も上書かれてしまう
                    sprintf(djp_stack, "%s", raw_stack);
                    djp_count = raw_count;
                    is_prev_like_combo_b = false;
                }
                if (raw >= X2HEX(X_A)) {
                    // 有効な値かを判定
                    raw_stack[raw_count++] = raw;
                    raw_stack[raw_count] = '\0';
                }
                if (dvorakjp >= X2HEX(X_A)) {
                    // 有効な値かを判定
                    djp_stack[djp_count++] = dvorakjp;
                    djp_stack[djp_count] = '\0';
                }
            }
            if (is_nagyou_possibility) {
                // 次の入力で「な」行チェック
                //current = line_na;
                next = current + current->miss;
                //return raw_count > 0;
            }
            if (current->hit > 0) {
                current = current + current->hit;
                return raw_count > 0;
            }
            if (is_vowels_expantion) {
                // 二重母音拡張と撥音拡張
                djp_stack[djp_count] = raw;
                if (djp_stack[djp_count] == X2HEX(X_N)) {
                    djp_stack[++djp_count] = X2HEX(X_N);
                }
                djp_stack[++djp_count] = '\0';
            }
            if (is_k_to_nn) {
                // 二重母音拡張と撥音拡張
                djp_stack[djp_count] = raw;
                djp_stack[++djp_count] = '\0';
            }
            if (djp_count > 0) {
                send_string_with_tapping_term(djp_stack, tapping_term);
                reset_dvorakjp_variables();
                return true;
            }
            reset_dvorakjp_variables();
            return false;
        }
        if (current->miss == 0) {
            if (next != NULL) {
                // 「な」行ではなかったので子音チェック
                current = next;
                next = NULL;
                continue;
            }
            break;
        }
        current = current + current->miss;
    }
    if (raw_count > 0) {
        send_string_with_tapping_term(raw_stack, tapping_term);
    }
    reset_dvorakjp_variables();
    return raw_count > 0;
}
