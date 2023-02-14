#pragma once

#ifdef DOKU_MOCKED
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "quantum/send_string/send_string_keycodes.h"
#define SAFE_RANGE 0
#include "keycodes/dvorak_keycodes.h"
#include "dvorakjp/tests/mock.h"
#define TAPPING_TERM 200
#else
#include "keymap.h"
#endif

// シフト押下時に動作変える場合に利用
#define DV_SHIFT (DV_Z - DV_1)

/*
dvorakjp拡張ビットフラグ
romaのraw,dvorakjpの上位ビットで使う
*/
#define EX1_BIT 0x20
#define EX2_BIT 0x40
#define EX3_BIT 0x60
#define EX4_BIT 0x80
#define EX5_BIT 0xa0
#define EX6_BIT 0xc0
#define EX7_BIT 0xe0

/*
16進から文字部分だけ取り出す
*/
#define X_MASK 0x001f // X_A(0x04) - X_Z(0x1d)
#define X_UNDEF X_A - 1 // X_A(0x04) - X_Z(0x1d)

/*
dvorakjp用マクロ
*/
#define X2HEX(x) _X2HEX(x)
#define X2HEX_EX1(x) (_X2HEX(x) | EX1_BIT)
#define X2HEX_EX2(x) (_X2HEX(x) | EX2_BIT)
#define X2HEX_EX3(x) (_X2HEX(x) | EX3_BIT)
#define X2HEX_EX4(x) (_X2HEX(x) | EX4_BIT)
#define X2HEX_EX5(x) (_X2HEX(x) | EX5_BIT)
#define X2HEX_EX6(x) (_X2HEX(x) | EX6_BIT)
#define X2HEX_EX7(x) (_X2HEX(x) | EX7_BIT)
#define _X2HEX(y) 0x##y

struct _roma {
    uint16_t keycode;
    char raw;
    char dvorakjp;
    char hit;
    char miss;
};

typedef struct _roma roma; 

void reset_dvorakjp_variables(void);
bool dvorakjp(uint16_t keycode, uint8_t tapping_term);
