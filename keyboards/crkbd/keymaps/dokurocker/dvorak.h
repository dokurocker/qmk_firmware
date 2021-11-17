/*
DVORAK
*/

#include "keymap.h"

/*
dvorakjp用マクロ
*/
#define X2HEX(x) _X2HEX(x)
#define _X2HEX(y) 0x##y

/*
dvorakjpモード
*/
bool is_dvorakjp(void);
void switch_dvorakjp(bool on);
void toggle_dvorakjp(void);
uint8_t lengthen_ss_delay(void);
uint8_t shorten_ss_delay(void);

/*
keyboard_post_init_user関数で利用
変換後のキー変更

@param keycode uint16_t keycode process_record_userの引数keycode
@param pressed bool process_record_userのrecord->event.pressed
@return process_record_userで戻すべき返り値
*/
void change_d2q_key(uint16_t d, uint16_t q, bool mods);

/*
process_record_user関数で利用

@param keycode uint16_t keycode process_record_userの引数keycode
@param pressed bool process_record_userのrecord->event.pressed
@return process_record_userで戻すべき返り値
*/
bool input_dvorak(uint16_t* keycode, bool pressed);
