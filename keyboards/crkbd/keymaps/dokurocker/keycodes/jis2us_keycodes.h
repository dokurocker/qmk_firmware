/*
JIS配列をUS配列にする
*/
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
    JU_GRV,
    JIS2US_NEW_SAFE_RANGE
};

#undef SAFE_RANGE
#define SAFE_RANGE JIS2US_NEW_SAFE_RANGE
