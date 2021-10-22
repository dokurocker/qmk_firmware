#include "jis2us.h"

const key_override_t ** key_overrides = NULL;

static bool disabled_backslash = false;

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
    static key_override_t ko_int1;
    static key_override_t ko_pipe;
    static key_override_t ko_grv;
    static key_override_t ko_tild;

    static key_override_t * _key_overrides[] = {
        &ko_at, &ko_circ, &ko_ampr, &ko_astr, &ko_lprn,
        &ko_rprn, &ko_unds, &ko_eql, &ko_plus, &ko_lbrc,
        &ko_rbrc, &ko_coln, &ko_quot, &ko_dqt, &ko_int1,
        &ko_pipe, &ko_grv, &ko_tild, NULL
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
    // バックスラッシュ
    ko_int1 = ko_make_with_layers_and_negmods(0, KC_INT1, disabled_backslash ? KC_INT3 : KC_INT1, ~0, (uint8_t)MOD_MASK_SHIFT);
    ko_pipe = ko_make_basic(MOD_MASK_SHIFT, KC_INT1, S(KC_INT3));
    // `
    ko_grv = ko_make_with_layers_and_negmods(0, KC_GRAVE, S(KC_LBRACKET), ~0, (uint8_t)MOD_MASK_SHIFT);
    // ~
    ko_tild = ko_make_basic(MOD_MASK_SHIFT, KC_GRAVE, S(KC_EQUAL));
    key_overrides = (const key_override_t **)_key_overrides;
}

void toggle_bs2yen(void)
{
    disabled_backslash = !disabled_backslash;
    ((key_override_t *)key_overrides[14])->replacement = disabled_backslash ? KC_INT3 : KC_INT1;
}
