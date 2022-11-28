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

/*
dvorakjp用マクロ
*/
#define X2HEX(x) _X2HEX(x)
#define _X2HEX(y) 0x##y

struct _roma {
    uint16_t keycode;
    char raw;
    char dvorakjp;
    char hit;
    char miss;
};

typedef struct _roma roma; 

bool dvorakjp(uint16_t keycode, uint8_t tapping_term);
