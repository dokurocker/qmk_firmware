/*
DVORAK
ただしShift以外のModifyキーは他のキーを指定可能
*/

enum dvorak_keycodes {
    DV_1 = SAFE_RANGE,
             DV_2,    DV_3,   DV_4, DV_5, DV_6, DV_7, DV_8, DV_9, DV_0, DV_LBRC, DV_RBRC,
    DV_QUOT, DV_COMM, DV_DOT, DV_P, DV_Y, DV_F, DV_G, DV_C, DV_R, DV_L, DV_SLSH, DV_EQL,
    DV_A,    DV_O,    DV_E,   DV_U, DV_I, DV_D, DV_H, DV_T, DV_N, DV_S, DV_MINS,
    DV_SCLN, DV_Q,    DV_J,   DV_K, DV_X, DV_B, DV_M, DV_W, DV_V, DV_Z,
    DVORAK_NEW_SAFE_RANGE
};

#undef SAFE_RANGE
#define SAFE_RANGE DVORAK_NEW_SAFE_RANGE
