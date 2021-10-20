/*
JIS配列をUS配列にする
*/

#include "keymap.h"

/*
バックスラッシュを「￥」にする
*/
void toggle_bs2yen(void);

/*
JIS配列をUS配列化
*/
void jis2us(layer_state_t layers);

/*
process_record_user関数で利用

@param keycode uint16_t keycode process_record_userの引数keycode
@param pressed bool process_record_userのrecord->event.pressed
@return process_record_userで戻すべき返り値
*/
bool input_jis2us(uint16_t keycode, bool pressed);
