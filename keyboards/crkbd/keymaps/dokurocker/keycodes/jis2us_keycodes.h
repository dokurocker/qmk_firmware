/*
JIS配列をUS配列にする
*/
enum jis2us_keycodes {
    JU_BSLS = SAFE_RANGE,
    JIS2US_NEW_SAFE_RANGE
};

#undef SAFE_RANGE
#define SAFE_RANGE JIS2US_NEW_SAFE_RANGE
