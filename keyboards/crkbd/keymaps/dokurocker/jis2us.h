/*
JIS配列をUS配列にする
*/

#include QMK_KEYBOARD_H

enum jis2us_keycodes {
    JU_2 = SAFE_RANGE,
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

#undef SAFE_RANGE
#define SAFE_RANGE JU_GRV + 1

/*
process_record_user関数で利用

@param keycode uint16_t keycode process_record_userの引数keycode
@param pressed bool process_record_userのrecord->event.pressed
@return process_record_userで戻すべき返り値
*/
bool input_jis2us(uint16_t keycode, bool pressed);
