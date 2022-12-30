#include "gtest/gtest.h"
#include <initializer_list>

extern "C" {
#include "dvorakjp/dvorakjp.h"
#include "mock.h"
#include "print.h"
}

class DvorakjpTest : public ::testing::Test {
   protected:

    void SetUp() override {
    }

    void TearDown() override {
    }

   public:
    static void ClearOutput() {
        memset(send_string_output, '\0', sizeof(send_string_output));
        send_string_output_index = 0;
        reset_dvorakjp_variables();
    }

    static void Input(std::initializer_list<uint16_t> keycodes) {
        char dvorakMap[] = "1234567890[]',.pyfgcrl/=aoeuidhtns-;qjkxbmwvz";
        for (auto k: keycodes) {
            if (!dvorakjp(k, 0)) {
                send_string_output[send_string_output_index++] = dvorakMap[k - DV_1];
            }
        }
    }
};

// 母音
TEST(DvorakjpTest, VowelsTest) {
    // あいうえお
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_A, DV_I, DV_U, DV_E, DV_O});
    ASSERT_STREQ("aiueo", send_string_output);
    // うぁ行(wh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_H, DV_A, DV_W, DV_H, DV_I, DV_W, DV_H, DV_U, DV_W, DV_H, DV_E, DV_W, DV_H, DV_O});
    ASSERT_STREQ("whawhiwhuwhewho", send_string_output);
    // うぃ,う,うぇ
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_I, DV_W, DV_U, DV_W, DV_E});
    ASSERT_STREQ("wiwuwe", send_string_output);
    // ぁ行
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_A, DV_X, DV_I, DV_X, DV_U, DV_X, DV_E, DV_X, DV_O});
    ASSERT_STREQ("xaxixuxexo", send_string_output);
    // いぇ
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_E});
    ASSERT_STREQ("ye", send_string_output);
    // うぁ行の撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_H, DV_SCLN, DV_W, DV_H, DV_X, DV_W, DV_H, DV_K, DV_W, DV_H, DV_J, DV_W, DV_H, DV_Q});
    ASSERT_STREQ("whannwhinnwhunnwhennwhonn", send_string_output);
    // うぃ,う,うぇ の撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_X, DV_W, DV_K, DV_W, DV_J});
    ASSERT_STREQ("winnwunnwenn", send_string_output);
    // ぁ行の撥音拡張(xx は っ, xk は ヵヶ で使用)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_SCLN, DV_X, DV_X, DV_X, DV_K, DV_X, DV_J, DV_X, DV_Q});
    ASSERT_STRNE("xannxinnxunnxennxonn", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_SCLN, DV_X, DV_J, DV_X, DV_Q});
    ASSERT_STREQ("xannxennxonn", send_string_output);
    // いぇ の撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_J});
    ASSERT_STREQ("yenn", send_string_output);
    // うぁ行の二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_H, DV_QUOT, DV_W, DV_H, DV_DOT, DV_W, DV_H, DV_COMM});
    ASSERT_STREQ("whaiwheiwhou", send_string_output);
    // うぇ の二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_DOT});
    ASSERT_STREQ("wei", send_string_output);
    // ぁ行の二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_QUOT, DV_X, DV_DOT, DV_X, DV_COMM});
    ASSERT_STREQ("xaixeixou", send_string_output);
    // いぇ の二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_DOT});
    ASSERT_STREQ("yei", send_string_output);
}

// か行
TEST(DvorakjpTest, KTest) {
    // 通常(k)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_A, DV_K, DV_I, DV_K, DV_U, DV_K, DV_E, DV_K, DV_O});
    ASSERT_STREQ("kakikukeko", send_string_output);
    // 通常(c)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_A, DV_C, DV_I, DV_C, DV_U, DV_C, DV_E, DV_C, DV_O});
    ASSERT_STREQ("kakikukeko", send_string_output);
    // 撥音拡張(k, kk は っ で使用)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_SCLN, DV_K, DV_X, DV_K, DV_K, DV_K, DV_J, DV_K, DV_Q});
    ASSERT_STRNE("kannkinnkunnkennkonn", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_SCLN, DV_K, DV_X, DV_K, DV_J, DV_K, DV_Q});
    ASSERT_STREQ("kannkinnkennkonn", send_string_output);
    // 撥音拡張(c)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_SCLN, DV_C, DV_X, DV_C, DV_K, DV_C, DV_J, DV_C, DV_Q});
    ASSERT_STREQ("kannkinnkunnkennkonn", send_string_output);
    // 二重母音拡張(k)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_QUOT, DV_K, DV_DOT, DV_K, DV_COMM});
    ASSERT_STREQ("kaikeikou", send_string_output);
    // 二重母音拡張(c)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_QUOT, DV_C, DV_DOT, DV_C, DV_COMM});
    ASSERT_STREQ("kaikeikou", send_string_output);
}

// きゃ行
TEST(DvorakjpTest, KyTest) {
    // 通常(ky)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_Y, DV_A, DV_K, DV_Y, DV_I, DV_K, DV_Y, DV_U, DV_K, DV_Y, DV_E, DV_K, DV_Y, DV_O});
    ASSERT_STREQ("kyakyikyukyekyo", send_string_output);
    // 通常(cy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_Y, DV_A, DV_C, DV_Y, DV_I, DV_C, DV_Y, DV_U, DV_C, DV_Y, DV_E, DV_C, DV_Y, DV_O});
    ASSERT_STREQ("kyakyikyukyekyo", send_string_output);
    // 通常(kh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_H, DV_A, DV_K, DV_H, DV_I, DV_K, DV_H, DV_U, DV_K, DV_H, DV_E, DV_K, DV_H, DV_O});
    ASSERT_STREQ("kyakyikyukyekyo", send_string_output);
    // 通常(ch) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_H, DV_A, DV_C, DV_H, DV_I, DV_C, DV_H, DV_U, DV_C, DV_H, DV_E, DV_C, DV_H, DV_O});
    ASSERT_STRNE("kyakyikyukyekyo", send_string_output);
    // 通常(kn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_N, DV_A, DV_K, DV_N, DV_I, DV_K, DV_N, DV_U, DV_K, DV_N, DV_E, DV_K, DV_N, DV_O});
    ASSERT_STRNE("kyakyikyukyekyo", send_string_output);
    // 通常(cn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_N, DV_A, DV_C, DV_N, DV_I, DV_C, DV_N, DV_U, DV_C, DV_N, DV_E, DV_C, DV_N, DV_O});
    ASSERT_STREQ("kyakyikyukyekyo", send_string_output);
    // 撥音拡張(ky)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_Y, DV_SCLN, DV_K, DV_Y, DV_X, DV_K, DV_Y, DV_K, DV_K, DV_Y, DV_J, DV_K, DV_Y, DV_Q});
    ASSERT_STREQ("kyannkyinnkyunnkyennkyonn", send_string_output);
    // 撥音拡張(cy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_Y, DV_SCLN, DV_C, DV_Y, DV_X, DV_C, DV_Y, DV_K, DV_C, DV_Y, DV_J, DV_C, DV_Y, DV_Q});
    ASSERT_STREQ("kyannkyinnkyunnkyennkyonn", send_string_output);
    // 撥音拡張(kh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_H, DV_SCLN, DV_K, DV_H, DV_X, DV_K, DV_H, DV_K, DV_K, DV_H, DV_J, DV_K, DV_H, DV_Q});
    ASSERT_STREQ("kyannkyinnkyunnkyennkyonn", send_string_output);
    // 撥音拡張(ch) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_H, DV_SCLN, DV_C, DV_H, DV_X, DV_C, DV_H, DV_K, DV_C, DV_H, DV_J, DV_C, DV_H, DV_Q});
    ASSERT_STRNE("kyannkyinnkyunnkyennkyonn", send_string_output);
    // 撥音拡張(kn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_N, DV_SCLN, DV_K, DV_N, DV_X, DV_K, DV_N, DV_K, DV_K, DV_N, DV_J, DV_K, DV_N, DV_Q});
    ASSERT_STRNE("kyannkyinnkyunnkyennkyonn", send_string_output);
    // 撥音拡張(cn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_N, DV_SCLN, DV_C, DV_N, DV_X, DV_C, DV_N, DV_K, DV_C, DV_N, DV_J, DV_C, DV_N, DV_Q});
    ASSERT_STREQ("kyannkyinnkyunnkyennkyonn", send_string_output);
    // 二重母音拡張(ky)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_Y, DV_QUOT, DV_K, DV_Y, DV_DOT, DV_K, DV_Y, DV_COMM});
    ASSERT_STREQ("kyaikyeikyou", send_string_output);
    // 二重母音拡張(cy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_Y, DV_QUOT, DV_C, DV_Y, DV_DOT, DV_C, DV_Y, DV_COMM});
    ASSERT_STREQ("kyaikyeikyou", send_string_output);
    // 二重母音拡張(kh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_H, DV_QUOT, DV_K, DV_H, DV_DOT, DV_K, DV_H, DV_COMM});
    ASSERT_STREQ("kyaikyeikyou", send_string_output);
    // 二重母音拡張(ch) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_H, DV_QUOT, DV_C, DV_H, DV_DOT, DV_C, DV_H, DV_COMM});
    ASSERT_STRNE("kyaikyeikyou", send_string_output);
    // 二重母音拡張(kn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_N, DV_QUOT, DV_K, DV_N, DV_DOT, DV_K, DV_N, DV_COMM});
    ASSERT_STRNE("kyaikyeikyou", send_string_output);
    // 二重母音拡張(cn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_N, DV_QUOT, DV_C, DV_N, DV_DOT, DV_C, DV_N, DV_COMM});
    ASSERT_STREQ("kyaikyeikyou", send_string_output);
}

// くぁ行
TEST(DvorakjpTest, QTest) {
    // 通常(q)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_A, DV_Q, DV_I, DV_Q, DV_U, DV_Q, DV_E, DV_Q, DV_O});
    ASSERT_STREQ("qaqiquqeqo", send_string_output);
    // 通常(kw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_W, DV_A, DV_K, DV_W, DV_I, DV_K, DV_W, DV_U, DV_K, DV_W, DV_E, DV_K, DV_W, DV_O});
    ASSERT_STREQ("kwakwikwukwekwo", send_string_output);
    // 通常(cw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_W, DV_A, DV_C, DV_W, DV_I, DV_C, DV_W, DV_U, DV_C, DV_W, DV_E, DV_C, DV_W, DV_O});
    ASSERT_STREQ("kwakwikwukwekwo", send_string_output);
    // 撥音拡張(q, qq は っ で使用)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_SCLN, DV_Q, DV_X, DV_Q, DV_K, DV_Q, DV_J, DV_Q, DV_Q});
    ASSERT_STRNE("qannqinnqunnqennqonn", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_SCLN, DV_Q, DV_X, DV_Q, DV_K, DV_Q, DV_J});
    ASSERT_STREQ("qannqinnqunnqenn", send_string_output);
    // 撥音拡張(kw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_W, DV_SCLN, DV_K, DV_W, DV_X, DV_K, DV_W, DV_K, DV_K, DV_W, DV_J, DV_K, DV_W, DV_Q});
    ASSERT_STREQ("kwannkwinnkwunnkwennkwonn", send_string_output);
    // 撥音拡張(cw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_W, DV_SCLN, DV_C, DV_W, DV_X, DV_C, DV_W, DV_K, DV_C, DV_W, DV_J, DV_C, DV_W, DV_Q});
    ASSERT_STREQ("kwannkwinnkwunnkwennkwonn", send_string_output);
    // 二重母音拡張(q)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_QUOT, DV_Q, DV_DOT, DV_Q, DV_COMM});
    ASSERT_STREQ("qaiqeiqou", send_string_output);
    // 二重母音拡張(kw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_W, DV_QUOT, DV_K, DV_W, DV_DOT, DV_K, DV_W, DV_COMM});
    ASSERT_STREQ("kwaikweikwou", send_string_output);
    // 二重母音拡張(cw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_W, DV_QUOT, DV_C, DV_W, DV_DOT, DV_C, DV_W, DV_COMM});
    ASSERT_STREQ("kwaikweikwou", send_string_output);
}

// くゃ行,くゎ
TEST(DvorakjpTest, QyTest) {
    // 通常(qy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_Y, DV_A, DV_Q, DV_Y, DV_I, DV_Q, DV_Y, DV_U, DV_Q, DV_Y, DV_E, DV_Q, DV_Y, DV_O});
    ASSERT_STREQ("qyaqyiqyuqyeqyo", send_string_output);
    // 通常(qh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_H, DV_A, DV_Q, DV_H, DV_I, DV_Q, DV_H, DV_U, DV_Q, DV_H, DV_E, DV_Q, DV_H, DV_O});
    ASSERT_STREQ("qyaqyiqyuqyeqyo", send_string_output);
    // 通常(qn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_N, DV_A, DV_Q, DV_N, DV_I, DV_Q, DV_N, DV_U, DV_Q, DV_N, DV_E, DV_Q, DV_N, DV_O});
    ASSERT_STRNE("qyaqyiqyuqyeqyo", send_string_output);
    // 撥音拡張(qy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_Y, DV_SCLN, DV_Q, DV_Y, DV_X, DV_Q, DV_Y, DV_K, DV_Q, DV_Y, DV_J, DV_Q, DV_Y, DV_Q});
    ASSERT_STREQ("qyannqyinnqyunnqyennqyonn", send_string_output);
    // 撥音拡張(qh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_H, DV_SCLN, DV_Q, DV_H, DV_X, DV_Q, DV_H, DV_K, DV_Q, DV_H, DV_J, DV_Q, DV_H, DV_Q});
    ASSERT_STREQ("qyannqyinnqyunnqyennqyonn", send_string_output);
    // 撥音拡張(qn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_N, DV_SCLN, DV_Q, DV_N, DV_X, DV_Q, DV_N, DV_K, DV_Q, DV_N, DV_J, DV_Q, DV_N, DV_Q});
    ASSERT_STRNE("qyannqyinnqyunnqyennqyonn", send_string_output);
    // 二重母音拡張(qy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_Y, DV_QUOT, DV_Q, DV_Y, DV_DOT, DV_Q, DV_Y, DV_COMM});
    ASSERT_STREQ("qyaiqyeiqyou", send_string_output);
    // 二重母音拡張(qh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_H, DV_QUOT, DV_Q, DV_H, DV_DOT, DV_Q, DV_H, DV_COMM});
    ASSERT_STREQ("qyaiqyeiqyou", send_string_output);
    // 二重母音拡張(qn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_N, DV_QUOT, DV_Q, DV_N, DV_DOT, DV_Q, DV_N, DV_COMM});
    ASSERT_STRNE("qyaiqyeiqyou", send_string_output);
    // くゎ
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_W, DV_A, DV_Q, DV_W, DV_SCLN, DV_Q, DV_W, DV_QUOT});
    ASSERT_STREQ("qwaqwannqwai", send_string_output);
}

// が行
TEST(DvorakjpTest, GTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_A, DV_G, DV_I, DV_G, DV_U, DV_G, DV_E, DV_G, DV_O});
    ASSERT_STREQ("gagigugego", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_SCLN, DV_G, DV_X, DV_G, DV_K, DV_G, DV_J, DV_G, DV_Q});
    ASSERT_STREQ("gannginngunngenngonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_QUOT, DV_G, DV_DOT, DV_G, DV_COMM});
    ASSERT_STREQ("gaigeigou", send_string_output);
}

// ぎゃ行
TEST(DvorakjpTest, GyTest) {
    // 通常(gy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_Y, DV_A, DV_G, DV_Y, DV_I, DV_G, DV_Y, DV_U, DV_G, DV_Y, DV_E, DV_G, DV_Y, DV_O});
    ASSERT_STREQ("gyagyigyugyegyo", send_string_output);
    // 通常(gh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_H, DV_A, DV_G, DV_H, DV_I, DV_G, DV_H, DV_U, DV_G, DV_H, DV_E, DV_G, DV_H, DV_O});
    ASSERT_STRNE("gyagyigyugyegyo", send_string_output);
    // 通常(gn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_N, DV_A, DV_G, DV_N, DV_I, DV_G, DV_N, DV_U, DV_G, DV_N, DV_E, DV_G, DV_N, DV_O});
    ASSERT_STREQ("gyagyigyugyegyo", send_string_output);
    // 撥音拡張(gy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_Y, DV_SCLN, DV_G, DV_Y, DV_X, DV_G, DV_Y, DV_K, DV_G, DV_Y, DV_J, DV_G, DV_Y, DV_Q});
    ASSERT_STREQ("gyanngyinngyunngyenngyonn", send_string_output);
    // 撥音拡張(gh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_H, DV_SCLN, DV_G, DV_H, DV_X, DV_G, DV_H, DV_K, DV_G, DV_H, DV_J, DV_G, DV_H, DV_Q});
    ASSERT_STRNE("gyanngyinngyunngyenngyonn", send_string_output);
    // 撥音拡張(gn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_N, DV_SCLN, DV_G, DV_N, DV_X, DV_G, DV_N, DV_K, DV_G, DV_N, DV_J, DV_G, DV_N, DV_Q});
    ASSERT_STREQ("gyanngyinngyunngyenngyonn", send_string_output);
    // 二重母音拡張(gy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_Y, DV_QUOT, DV_G, DV_Y, DV_DOT, DV_G, DV_Y, DV_COMM});
    ASSERT_STREQ("gyaigyeigyou", send_string_output);
    // 二重母音拡張(gh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_H, DV_QUOT, DV_G, DV_H, DV_DOT, DV_G, DV_H, DV_COMM});
    ASSERT_STRNE("gyaigyeigyou", send_string_output);
    // 二重母音拡張(gn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_N, DV_QUOT, DV_G, DV_N, DV_DOT, DV_G, DV_N, DV_COMM});
    ASSERT_STREQ("gyaigyeigyou", send_string_output);
}

// ぐぁ行
TEST(DvorakjpTest, GwTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_W, DV_A, DV_G, DV_W, DV_I, DV_G, DV_W, DV_U, DV_G, DV_W, DV_E, DV_G, DV_W, DV_O});
    ASSERT_STREQ("gwagwigwugwegwo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_W, DV_SCLN, DV_G, DV_W, DV_X, DV_G, DV_W, DV_K, DV_G, DV_W, DV_J, DV_G, DV_W, DV_Q});
    ASSERT_STREQ("gwanngwinngwunngwenngwonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_W, DV_QUOT, DV_G, DV_W, DV_DOT, DV_G, DV_W, DV_COMM});
    ASSERT_STREQ("gwaigweigwou", send_string_output);
}

// ヵ,ヶ
TEST(DvorakjpTest, XkTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_K, DV_A, DV_X, DV_K, DV_E, DV_X, DV_C, DV_A, DV_X, DV_C, DV_E});
    ASSERT_STREQ("xkaxkexkaxke", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_K, DV_SCLN, DV_X, DV_K, DV_J, DV_X, DV_C, DV_SCLN, DV_X, DV_C, DV_J});
    ASSERT_STREQ("xkannxkennxkannxkenn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_K, DV_QUOT, DV_X, DV_K, DV_DOT, DV_X, DV_C, DV_QUOT, DV_X, DV_C, DV_DOT});
    ASSERT_STREQ("xkaixkeixkaixkei", send_string_output);
}

// さ行
TEST(DvorakjpTest, STest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_A, DV_S, DV_I, DV_S, DV_U, DV_S, DV_E, DV_S, DV_O});
    ASSERT_STREQ("sasisuseso", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_SCLN, DV_S, DV_X, DV_S, DV_K, DV_S, DV_J, DV_S, DV_Q});
    ASSERT_STREQ("sannsinnsunnsennsonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_QUOT, DV_S, DV_DOT, DV_S, DV_COMM});
    ASSERT_STREQ("saiseisou", send_string_output);
}

// しゃ行
TEST(DvorakjpTest, SyTest) {
    // 通常(sy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_Y, DV_A, DV_S, DV_Y, DV_I, DV_S, DV_Y, DV_U, DV_S, DV_Y, DV_E, DV_S, DV_Y, DV_O});
    ASSERT_STREQ("syasyisyusyesyo", send_string_output);
    // 通常(sh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_H, DV_A, DV_S, DV_H, DV_I, DV_S, DV_H, DV_U, DV_S, DV_H, DV_E, DV_S, DV_H, DV_O});
    ASSERT_STREQ("syasyisyusyesyo", send_string_output);
    // 通常(sn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_N, DV_A, DV_S, DV_N, DV_I, DV_S, DV_N, DV_U, DV_S, DV_N, DV_E, DV_S, DV_N, DV_O});
    ASSERT_STRNE("syasyisyusyesyo", send_string_output);
    // 撥音拡張(sy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_Y, DV_SCLN, DV_S, DV_Y, DV_X, DV_S, DV_Y, DV_K, DV_S, DV_Y, DV_J, DV_S, DV_Y, DV_Q});
    ASSERT_STREQ("syannsyinnsyunnsyennsyonn", send_string_output);
    // 撥音拡張(sh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_H, DV_SCLN, DV_S, DV_H, DV_X, DV_S, DV_H, DV_K, DV_S, DV_H, DV_J, DV_S, DV_H, DV_Q});
    ASSERT_STREQ("syannsyinnsyunnsyennsyonn", send_string_output);
    // 撥音拡張(sn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_N, DV_SCLN, DV_S, DV_N, DV_X, DV_S, DV_N, DV_K, DV_S, DV_N, DV_J, DV_S, DV_N, DV_Q});
    ASSERT_STRNE("syannsyinnsyunnsyennsyonn", send_string_output);
    // 二重母音拡張(sy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_Y, DV_QUOT, DV_S, DV_Y, DV_DOT, DV_S, DV_Y, DV_COMM});
    ASSERT_STREQ("syaisyeisyou", send_string_output);
    // 二重母音拡張(sh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_H, DV_QUOT, DV_S, DV_H, DV_DOT, DV_S, DV_H, DV_COMM});
    ASSERT_STREQ("syaisyeisyou", send_string_output);
    // 二重母音拡張(sn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_N, DV_QUOT, DV_S, DV_N, DV_DOT, DV_S, DV_N, DV_COMM});
    ASSERT_STRNE("syaisyeisyou", send_string_output);
}

// すぁ行
TEST(DvorakjpTest, SwTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_W, DV_A, DV_S, DV_W, DV_I, DV_S, DV_W, DV_U, DV_S, DV_W, DV_E, DV_S, DV_W, DV_O});
    ASSERT_STREQ("swaswiswusweswo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_W, DV_SCLN, DV_S, DV_W, DV_X, DV_S, DV_W, DV_K, DV_S, DV_W, DV_J, DV_S, DV_W, DV_Q});
    ASSERT_STREQ("swannswinnswunnswennswonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_W, DV_QUOT, DV_S, DV_W, DV_DOT, DV_S, DV_W, DV_COMM});
    ASSERT_STREQ("swaisweiswou", send_string_output);
}

// ざ行
TEST(DvorakjpTest, ZTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_A, DV_Z, DV_I, DV_Z, DV_U, DV_Z, DV_E, DV_Z, DV_O});
    ASSERT_STREQ("zazizuzezo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_SCLN, DV_Z, DV_X, DV_Z, DV_K, DV_Z, DV_J, DV_Z, DV_Q});
    ASSERT_STREQ("zannzinnzunnzennzonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_QUOT, DV_Z, DV_DOT, DV_Z, DV_COMM});
    ASSERT_STREQ("zaizeizou", send_string_output);
}

// じゃ行
TEST(DvorakjpTest, ZyTest) {
    // 通常(zy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_Y, DV_A, DV_Z, DV_Y, DV_I, DV_Z, DV_Y, DV_U, DV_Z, DV_Y, DV_E, DV_Z, DV_Y, DV_O});
    ASSERT_STREQ("zyazyizyuzyezyo", send_string_output);
    // 通常(zh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_H, DV_A, DV_Z, DV_H, DV_I, DV_Z, DV_H, DV_U, DV_Z, DV_H, DV_E, DV_Z, DV_H, DV_O});
    ASSERT_STREQ("zyazyizyuzyezyo", send_string_output);
    // 通常(zn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_N, DV_A, DV_Z, DV_N, DV_I, DV_Z, DV_N, DV_U, DV_Z, DV_N, DV_E, DV_Z, DV_N, DV_O});
    ASSERT_STRNE("zyazyizyuzyezyo", send_string_output);
    // 撥音拡張(zy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_Y, DV_SCLN, DV_Z, DV_Y, DV_X, DV_Z, DV_Y, DV_K, DV_Z, DV_Y, DV_J, DV_Z, DV_Y, DV_Q});
    ASSERT_STREQ("zyannzyinnzyunnzyennzyonn", send_string_output);
    // 撥音拡張(zh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_H, DV_SCLN, DV_Z, DV_H, DV_X, DV_Z, DV_H, DV_K, DV_Z, DV_H, DV_J, DV_Z, DV_H, DV_Q});
    ASSERT_STREQ("zyannzyinnzyunnzyennzyonn", send_string_output);
    // 撥音拡張(zn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_N, DV_SCLN, DV_Z, DV_N, DV_X, DV_Z, DV_N, DV_K, DV_Z, DV_N, DV_J, DV_Z, DV_N, DV_Q});
    ASSERT_STRNE("zyannzyinnzyunnzyennzyonn", send_string_output);
    // 二重母音拡張(zy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_Y, DV_QUOT, DV_Z, DV_Y, DV_DOT, DV_Z, DV_Y, DV_COMM});
    ASSERT_STREQ("zyaizyeizyou", send_string_output);
    // 二重母音拡張(zh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_H, DV_QUOT, DV_Z, DV_H, DV_DOT, DV_Z, DV_H, DV_COMM});
    ASSERT_STREQ("zyaizyeizyou", send_string_output);
    // 二重母音拡張(zn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_N, DV_QUOT, DV_Z, DV_N, DV_DOT, DV_Z, DV_N, DV_COMM});
    ASSERT_STRNE("zyaizyeizyou", send_string_output);
}

// ずぁ行
TEST(DvorakjpTest, ZwTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_W, DV_A, DV_Z, DV_W, DV_I, DV_Z, DV_W, DV_U, DV_Z, DV_W, DV_E, DV_Z, DV_W, DV_O});
    ASSERT_STREQ("zwazwizwuzwezwo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_W, DV_SCLN, DV_Z, DV_W, DV_X, DV_Z, DV_W, DV_K, DV_Z, DV_W, DV_J, DV_Z, DV_W, DV_Q});
    ASSERT_STREQ("zwannzwinnzwunnzwennzwonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_W, DV_QUOT, DV_Z, DV_W, DV_DOT, DV_Z, DV_W, DV_COMM});
    ASSERT_STREQ("zwaizweizwou", send_string_output);
}

// た行
TEST(DvorakjpTest, TTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_A, DV_T, DV_I, DV_T, DV_U, DV_T, DV_E, DV_T, DV_O});
    ASSERT_STREQ("tatituteto", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_SCLN, DV_T, DV_X, DV_T, DV_K, DV_T, DV_J, DV_T, DV_Q});
    ASSERT_STREQ("tanntinntunntenntonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_QUOT, DV_T, DV_DOT, DV_T, DV_COMM});
    ASSERT_STREQ("taiteitou", send_string_output);
}

// ちゃ行
TEST(DvorakjpTest, TyTest) {
    // 通常(ty)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_Y, DV_A, DV_T, DV_Y, DV_I, DV_T, DV_Y, DV_U, DV_T, DV_Y, DV_E, DV_T, DV_Y, DV_O});
    ASSERT_STREQ("tyatyityutyetyo", send_string_output);
    // 通常(th) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_H, DV_A, DV_T, DV_H, DV_I, DV_T, DV_H, DV_U, DV_T, DV_H, DV_E, DV_T, DV_H, DV_O});
    ASSERT_STRNE("tyatyityutyetyo", send_string_output);
    // 通常(tn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_N, DV_A, DV_T, DV_N, DV_I, DV_T, DV_N, DV_U, DV_T, DV_N, DV_E, DV_T, DV_N, DV_O});
    ASSERT_STREQ("tyatyityutyetyo", send_string_output);
    // 撥音拡張(ty)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_Y, DV_SCLN, DV_T, DV_Y, DV_X, DV_T, DV_Y, DV_K, DV_T, DV_Y, DV_J, DV_T, DV_Y, DV_Q});
    ASSERT_STREQ("tyanntyinntyunntyenntyonn", send_string_output);
    // 撥音拡張(th) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_H, DV_SCLN, DV_T, DV_H, DV_X, DV_T, DV_H, DV_K, DV_T, DV_H, DV_J, DV_T, DV_H, DV_Q});
    ASSERT_STRNE("tyanntyinntyunntyenntyonn", send_string_output);
    // 撥音拡張(tn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_N, DV_SCLN, DV_T, DV_N, DV_X, DV_T, DV_N, DV_K, DV_T, DV_N, DV_J, DV_T, DV_N, DV_Q});
    ASSERT_STREQ("tyanntyinntyunntyenntyonn", send_string_output);
    // 二重母音拡張(ty)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_Y, DV_QUOT, DV_T, DV_Y, DV_DOT, DV_T, DV_Y, DV_COMM});
    ASSERT_STREQ("tyaityeityou", send_string_output);
    // 二重母音拡張(th) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_H, DV_QUOT, DV_T, DV_H, DV_DOT, DV_T, DV_H, DV_COMM});
    ASSERT_STRNE("tyaityeityou", send_string_output);
    // 二重母音拡張(tn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_N, DV_QUOT, DV_T, DV_N, DV_DOT, DV_T, DV_N, DV_COMM});
    ASSERT_STREQ("tyaityeityou", send_string_output);
}

// つぁ行
TEST(DvorakjpTest, TsTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_S, DV_A, DV_T, DV_S, DV_I, DV_T, DV_S, DV_U, DV_T, DV_S, DV_E, DV_T, DV_S, DV_O});
    ASSERT_STREQ("tsatsitsutsetso", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_S, DV_SCLN, DV_T, DV_S, DV_X, DV_T, DV_S, DV_K, DV_T, DV_S, DV_J, DV_T, DV_S, DV_Q});
    ASSERT_STREQ("tsanntsinntsunntsenntsonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_S, DV_QUOT, DV_T, DV_S, DV_DOT, DV_T, DV_S, DV_COMM});
    ASSERT_STREQ("tsaitseitsou", send_string_output);
}

// てゃ行
TEST(DvorakjpTest, ThTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_H, DV_A, DV_T, DV_H, DV_I, DV_T, DV_H, DV_U, DV_T, DV_H, DV_E, DV_T, DV_H, DV_O});
    ASSERT_STREQ("thathithuthetho", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_H, DV_SCLN, DV_T, DV_H, DV_X, DV_T, DV_H, DV_K, DV_T, DV_H, DV_J, DV_T, DV_H, DV_Q});
    ASSERT_STREQ("thannthinnthunnthennthonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_H, DV_QUOT, DV_T, DV_H, DV_DOT, DV_T, DV_H, DV_COMM});
    ASSERT_STREQ("thaitheithou", send_string_output);
}

// とぁ行
TEST(DvorakjpTest, TwTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_W, DV_A, DV_T, DV_W, DV_I, DV_T, DV_W, DV_U, DV_T, DV_W, DV_E, DV_T, DV_W, DV_O});
    ASSERT_STREQ("twatwitwutwetwo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_W, DV_SCLN, DV_T, DV_W, DV_X, DV_T, DV_W, DV_K, DV_T, DV_W, DV_J, DV_T, DV_W, DV_Q});
    ASSERT_STREQ("twanntwinntwunntwenntwonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_W, DV_QUOT, DV_T, DV_W, DV_DOT, DV_T, DV_W, DV_COMM});
    ASSERT_STREQ("twaitweitwou", send_string_output);
}

// だ行
TEST(DvorakjpTest, DTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_A, DV_D, DV_I, DV_D, DV_U, DV_D, DV_E, DV_D, DV_O});
    ASSERT_STREQ("dadidudedo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_SCLN, DV_D, DV_X, DV_D, DV_K, DV_D, DV_J, DV_D, DV_Q});
    ASSERT_STREQ("danndinndunndenndonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_QUOT, DV_D, DV_DOT, DV_D, DV_COMM});
    ASSERT_STREQ("daideidou", send_string_output);
}

// ぢゃ行
TEST(DvorakjpTest, DyTest) {
    // 通常(dy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_Y, DV_A, DV_D, DV_Y, DV_I, DV_D, DV_Y, DV_U, DV_D, DV_Y, DV_E, DV_D, DV_Y, DV_O});
    ASSERT_STREQ("dyadyidyudyedyo", send_string_output);
    // 通常(dh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_H, DV_A, DV_D, DV_H, DV_I, DV_D, DV_H, DV_U, DV_D, DV_H, DV_E, DV_D, DV_H, DV_O});
    ASSERT_STRNE("dyadyidyudyedyo", send_string_output);
    // 通常(dn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_N, DV_A, DV_D, DV_N, DV_I, DV_D, DV_N, DV_U, DV_D, DV_N, DV_E, DV_D, DV_N, DV_O});
    ASSERT_STREQ("dyadyidyudyedyo", send_string_output);
    // 撥音拡張(dy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_Y, DV_SCLN, DV_D, DV_Y, DV_X, DV_D, DV_Y, DV_K, DV_D, DV_Y, DV_J, DV_D, DV_Y, DV_Q});
    ASSERT_STREQ("dyanndyinndyunndyenndyonn", send_string_output);
    // 撥音拡張(dh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_H, DV_SCLN, DV_D, DV_H, DV_X, DV_D, DV_H, DV_K, DV_D, DV_H, DV_J, DV_D, DV_H, DV_Q});
    ASSERT_STRNE("dyanndyinndyunndyenndyonn", send_string_output);
    // 撥音拡張(dn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_N, DV_SCLN, DV_D, DV_N, DV_X, DV_D, DV_N, DV_K, DV_D, DV_N, DV_J, DV_D, DV_N, DV_Q});
    ASSERT_STREQ("dyanndyinndyunndyenndyonn", send_string_output);
    // 二重母音拡張(dy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_Y, DV_QUOT, DV_D, DV_Y, DV_DOT, DV_D, DV_Y, DV_COMM});
    ASSERT_STREQ("dyaidyeidyou", send_string_output);
    // 二重母音拡張(dh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_H, DV_QUOT, DV_D, DV_H, DV_DOT, DV_D, DV_H, DV_COMM});
    ASSERT_STRNE("dyaidyeidyou", send_string_output);
    // 二重母音拡張(dn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_N, DV_QUOT, DV_D, DV_N, DV_DOT, DV_D, DV_N, DV_COMM});
    ASSERT_STREQ("dyaidyeidyou", send_string_output);
}


// てゃ行
TEST(DvorakjpTest, DhTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_H, DV_A, DV_D, DV_H, DV_I, DV_D, DV_H, DV_U, DV_D, DV_H, DV_E, DV_D, DV_H, DV_O});
    ASSERT_STREQ("dhadhidhudhedho", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_H, DV_SCLN, DV_D, DV_H, DV_X, DV_D, DV_H, DV_K, DV_D, DV_H, DV_J, DV_D, DV_H, DV_Q});
    ASSERT_STREQ("dhanndhinndhunndhenndhonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_H, DV_QUOT, DV_D, DV_H, DV_DOT, DV_D, DV_H, DV_COMM});
    ASSERT_STREQ("dhaidheidhou", send_string_output);
}

// どぁ行
TEST(DvorakjpTest, DwTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_W, DV_A, DV_D, DV_W, DV_I, DV_D, DV_W, DV_U, DV_D, DV_W, DV_E, DV_D, DV_W, DV_O});
    ASSERT_STREQ("dwadwidwudwedwo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_W, DV_SCLN, DV_D, DV_W, DV_X, DV_D, DV_W, DV_K, DV_D, DV_W, DV_J, DV_D, DV_W, DV_Q});
    ASSERT_STREQ("dwanndwinndwunndwenndwonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_W, DV_QUOT, DV_D, DV_W, DV_DOT, DV_D, DV_W, DV_COMM});
    ASSERT_STREQ("dwaidweidwou", send_string_output);
}

// な行
TEST(DvorakjpTest, NTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_A, DV_N, DV_I, DV_N, DV_U, DV_N, DV_E, DV_N, DV_O});
    ASSERT_STREQ("naninuneno", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_SCLN, DV_N, DV_X, DV_N, DV_K, DV_N, DV_J, DV_N, DV_Q});
    ASSERT_STREQ("nannninnnunnnennnonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_QUOT, DV_N, DV_DOT, DV_N, DV_COMM});
    ASSERT_STREQ("naineinou", send_string_output);
}

// にゃ行
TEST(DvorakjpTest, NyTest) {
    // 通常(ny)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_Y, DV_A, DV_N, DV_Y, DV_I, DV_N, DV_Y, DV_U, DV_N, DV_Y, DV_E, DV_N, DV_Y, DV_O});
    ASSERT_STREQ("nyanyinyunyenyo", send_string_output);
    // 通常(nh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_H, DV_A, DV_N, DV_H, DV_I, DV_N, DV_H, DV_U, DV_N, DV_H, DV_E, DV_N, DV_H, DV_O});
    ASSERT_STREQ("nyanyinyunyenyo", send_string_output);
    // 通常(nn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_N, DV_A, DV_N, DV_N, DV_I, DV_N, DV_N, DV_U, DV_N, DV_N, DV_E, DV_N, DV_N, DV_O});
    ASSERT_STRNE("nyanyinyunyenyo", send_string_output);
    // 撥音拡張(ny)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_Y, DV_SCLN, DV_N, DV_Y, DV_X, DV_N, DV_Y, DV_K, DV_N, DV_Y, DV_J, DV_N, DV_Y, DV_Q});
    ASSERT_STREQ("nyannnyinnnyunnnyennnyonn", send_string_output);
    // 撥音拡張(nh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_H, DV_SCLN, DV_N, DV_H, DV_X, DV_N, DV_H, DV_K, DV_N, DV_H, DV_J, DV_N, DV_H, DV_Q});
    ASSERT_STREQ("nyannnyinnnyunnnyennnyonn", send_string_output);
    // 撥音拡張(nn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_N, DV_SCLN, DV_N, DV_N, DV_X, DV_N, DV_N, DV_K, DV_N, DV_N, DV_J, DV_N, DV_N, DV_Q});
    ASSERT_STRNE("nyannnyinnnyunnnyennnyonn", send_string_output);
    // 二重母音拡張(ny)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_Y, DV_QUOT, DV_N, DV_Y, DV_DOT, DV_N, DV_Y, DV_COMM});
    ASSERT_STREQ("nyainyeinyou", send_string_output);
    // 二重母音拡張(nh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_H, DV_QUOT, DV_N, DV_H, DV_DOT, DV_N, DV_H, DV_COMM});
    ASSERT_STREQ("nyainyeinyou", send_string_output);
    // 二重母音拡張(nn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_N, DV_QUOT, DV_N, DV_N, DV_DOT, DV_N, DV_N, DV_COMM});
    ASSERT_STRNE("nyainyeinyou", send_string_output);
}

// は行
TEST(DvorakjpTest, HTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_A, DV_H, DV_I, DV_H, DV_U, DV_H, DV_E, DV_H, DV_O});
    ASSERT_STREQ("hahihuheho", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_SCLN, DV_H, DV_X, DV_H, DV_K, DV_H, DV_J, DV_H, DV_Q});
    ASSERT_STREQ("hannhinnhunnhennhonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_QUOT, DV_H, DV_DOT, DV_H, DV_COMM});
    ASSERT_STREQ("haiheihou", send_string_output);
}

// ひゃ行
TEST(DvorakjpTest, HyTest) {
    // 通常(hy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_Y, DV_A, DV_H, DV_Y, DV_I, DV_H, DV_Y, DV_U, DV_H, DV_Y, DV_E, DV_H, DV_Y, DV_O});
    ASSERT_STREQ("hyahyihyuhyehyo", send_string_output);
    // 通常(hh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_H, DV_A, DV_H, DV_H, DV_I, DV_H, DV_H, DV_U, DV_H, DV_H, DV_E, DV_H, DV_H, DV_O});
    ASSERT_STRNE("hyahyihyuhyehyo", send_string_output);
    // 通常(hn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_N, DV_A, DV_H, DV_N, DV_I, DV_H, DV_N, DV_U, DV_H, DV_N, DV_E, DV_H, DV_N, DV_O});
    ASSERT_STREQ("hyahyihyuhyehyo", send_string_output);
    // 撥音拡張(hy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_Y, DV_SCLN, DV_H, DV_Y, DV_X, DV_H, DV_Y, DV_K, DV_H, DV_Y, DV_J, DV_H, DV_Y, DV_Q});
    ASSERT_STREQ("hyannhyinnhyunnhyennhyonn", send_string_output);
    // 撥音拡張(hh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_H, DV_SCLN, DV_H, DV_H, DV_X, DV_H, DV_H, DV_K, DV_H, DV_H, DV_J, DV_H, DV_H, DV_Q});
    ASSERT_STRNE("hyannhyinnhyunnhyennhyonn", send_string_output);
    // 撥音拡張(hn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_N, DV_SCLN, DV_H, DV_N, DV_X, DV_H, DV_N, DV_K, DV_H, DV_N, DV_J, DV_H, DV_N, DV_Q});
    ASSERT_STREQ("hyannhyinnhyunnhyennhyonn", send_string_output);
    // 二重母音拡張(hy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_Y, DV_QUOT, DV_H, DV_Y, DV_DOT, DV_H, DV_Y, DV_COMM});
    ASSERT_STREQ("hyaihyeihyou", send_string_output);
    // 二重母音拡張(hh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_H, DV_QUOT, DV_H, DV_H, DV_DOT, DV_H, DV_H, DV_COMM});
    ASSERT_STRNE("hyaihyeihyou", send_string_output);
    // 二重母音拡張(hn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_N, DV_QUOT, DV_H, DV_N, DV_DOT, DV_H, DV_N, DV_COMM});
    ASSERT_STREQ("hyaihyeihyou", send_string_output);
}

// ふぁ行
TEST(DvorakjpTest, FTest) {
    // 通常(f)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_A, DV_F, DV_I, DV_F, DV_U, DV_F, DV_E, DV_F, DV_O});
    ASSERT_STREQ("fafifufefo", send_string_output);
    // 通常(hw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_W, DV_A, DV_H, DV_W, DV_I, DV_H, DV_W, DV_U, DV_H, DV_W, DV_E, DV_H, DV_W, DV_O});
    ASSERT_STREQ("hwahwihwuhwehwo", send_string_output);
    // 撥音拡張(f)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_SCLN, DV_F, DV_X, DV_F, DV_K, DV_F, DV_J, DV_F, DV_Q});
    ASSERT_STREQ("fannfinnfunnfennfonn", send_string_output);
    // 撥音拡張(hw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_W, DV_SCLN, DV_H, DV_W, DV_X, DV_H, DV_W, DV_K, DV_H, DV_W, DV_J, DV_H, DV_W, DV_Q});
    ASSERT_STREQ("hwannhwinnhwunnhwennhwonn", send_string_output);
    // 二重母音拡張(f)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_QUOT, DV_F, DV_DOT, DV_F, DV_COMM});
    ASSERT_STREQ("faifeifou", send_string_output);
    // 二重母音拡張(hw)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_W, DV_QUOT, DV_H, DV_W, DV_DOT, DV_H, DV_W, DV_COMM});
    ASSERT_STREQ("hwaihweihwou", send_string_output);
}

// ふゃ行
TEST(DvorakjpTest, FyTest) {
    // 通常(fy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_Y, DV_A, DV_F, DV_Y, DV_I, DV_F, DV_Y, DV_U, DV_F, DV_Y, DV_E, DV_F, DV_Y, DV_O});
    ASSERT_STREQ("fyafyifyufyefyo", send_string_output);
    // 通常(fh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_H, DV_A, DV_F, DV_H, DV_I, DV_F, DV_H, DV_U, DV_F, DV_H, DV_E, DV_F, DV_H, DV_O});
    ASSERT_STRNE("fyafyifyufyefyo", send_string_output);
    // 通常(fn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_N, DV_A, DV_F, DV_N, DV_I, DV_F, DV_N, DV_U, DV_F, DV_N, DV_E, DV_F, DV_N, DV_O});
    ASSERT_STREQ("fyafyifyufyefyo", send_string_output);
    // 撥音拡張(fy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_Y, DV_SCLN, DV_F, DV_Y, DV_X, DV_F, DV_Y, DV_K, DV_F, DV_Y, DV_J, DV_F, DV_Y, DV_Q});
    ASSERT_STREQ("fyannfyinnfyunnfyennfyonn", send_string_output);
    // 撥音拡張(fh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_H, DV_SCLN, DV_F, DV_H, DV_X, DV_F, DV_H, DV_K, DV_F, DV_H, DV_J, DV_F, DV_H, DV_Q});
    ASSERT_STRNE("fyannfyinnfyunnfyennfyonn", send_string_output);
    // 撥音拡張(fn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_N, DV_SCLN, DV_F, DV_N, DV_X, DV_F, DV_N, DV_K, DV_F, DV_N, DV_J, DV_F, DV_N, DV_Q});
    ASSERT_STREQ("fyannfyinnfyunnfyennfyonn", send_string_output);
    // 二重母音拡張(fy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_Y, DV_QUOT, DV_F, DV_Y, DV_DOT, DV_F, DV_Y, DV_COMM});
    ASSERT_STREQ("fyaifyeifyou", send_string_output);
    // 二重母音拡張(fh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_H, DV_QUOT, DV_F, DV_H, DV_DOT, DV_F, DV_H, DV_COMM});
    ASSERT_STRNE("fyaifyeifyou", send_string_output);
    // 二重母音拡張(fn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_F, DV_N, DV_QUOT, DV_F, DV_N, DV_DOT, DV_F, DV_N, DV_COMM});
    ASSERT_STREQ("fyaifyeifyou", send_string_output);
}

// ば行
TEST(DvorakjpTest, BTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_A, DV_B, DV_I, DV_B, DV_U, DV_B, DV_E, DV_B, DV_O});
    ASSERT_STREQ("babibubebo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_SCLN, DV_B, DV_X, DV_B, DV_K, DV_B, DV_J, DV_B, DV_Q});
    ASSERT_STREQ("bannbinnbunnbennbonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_QUOT, DV_B, DV_DOT, DV_B, DV_COMM});
    ASSERT_STREQ("baibeibou", send_string_output);
}

// びゃ行
TEST(DvorakjpTest, ByTest) {
    // 通常(by)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_Y, DV_A, DV_B, DV_Y, DV_I, DV_B, DV_Y, DV_U, DV_B, DV_Y, DV_E, DV_B, DV_Y, DV_O});
    ASSERT_STREQ("byabyibyubyebyo", send_string_output);
    // 通常(bh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_H, DV_A, DV_B, DV_H, DV_I, DV_B, DV_H, DV_U, DV_B, DV_H, DV_E, DV_B, DV_H, DV_O});
    ASSERT_STRNE("byabyibyubyebyo", send_string_output);
    // 通常(bn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_N, DV_A, DV_B, DV_N, DV_I, DV_B, DV_N, DV_U, DV_B, DV_N, DV_E, DV_B, DV_N, DV_O});
    ASSERT_STREQ("byabyibyubyebyo", send_string_output);
    // 撥音拡張(by)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_Y, DV_SCLN, DV_B, DV_Y, DV_X, DV_B, DV_Y, DV_K, DV_B, DV_Y, DV_J, DV_B, DV_Y, DV_Q});
    ASSERT_STREQ("byannbyinnbyunnbyennbyonn", send_string_output);
    // 撥音拡張(bh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_H, DV_SCLN, DV_B, DV_H, DV_X, DV_B, DV_H, DV_K, DV_B, DV_H, DV_J, DV_B, DV_H, DV_Q});
    ASSERT_STRNE("byannbyinnbyunnbyennbyonn", send_string_output);
    // 撥音拡張(bn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_N, DV_SCLN, DV_B, DV_N, DV_X, DV_B, DV_N, DV_K, DV_B, DV_N, DV_J, DV_B, DV_N, DV_Q});
    ASSERT_STREQ("byannbyinnbyunnbyennbyonn", send_string_output);
    // 二重母音拡張(by)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_Y, DV_QUOT, DV_B, DV_Y, DV_DOT, DV_B, DV_Y, DV_COMM});
    ASSERT_STREQ("byaibyeibyou", send_string_output);
    // 二重母音拡張(bh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_H, DV_QUOT, DV_B, DV_H, DV_DOT, DV_B, DV_H, DV_COMM});
    ASSERT_STRNE("byaibyeibyou", send_string_output);
    // 二重母音拡張(bn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_N, DV_QUOT, DV_B, DV_N, DV_DOT, DV_B, DV_N, DV_COMM});
    ASSERT_STREQ("byaibyeibyou", send_string_output);
}

// ゔぁ行
TEST(DvorakjpTest, VTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_A, DV_V, DV_I, DV_V, DV_U, DV_V, DV_E, DV_V, DV_O});
    ASSERT_STREQ("vavivuvevo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_SCLN, DV_V, DV_X, DV_V, DV_K, DV_V, DV_J, DV_V, DV_Q});
    ASSERT_STREQ("vannvinnvunnvennvonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_QUOT, DV_V, DV_DOT, DV_V, DV_COMM});
    ASSERT_STREQ("vaiveivou", send_string_output);
}

// ゔゃ行
TEST(DvorakjpTest, VyTest) {
    // 通常(vy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_Y, DV_A, DV_V, DV_Y, DV_I, DV_V, DV_Y, DV_U, DV_V, DV_Y, DV_E, DV_V, DV_Y, DV_O});
    ASSERT_STREQ("vyavyivyuvyevyo", send_string_output);
    // 通常(vh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_H, DV_A, DV_V, DV_H, DV_I, DV_V, DV_H, DV_U, DV_V, DV_H, DV_E, DV_V, DV_H, DV_O});
    ASSERT_STREQ("vyavyivyuvyevyo", send_string_output);
    // 通常(vn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_N, DV_A, DV_V, DV_N, DV_I, DV_V, DV_N, DV_U, DV_V, DV_N, DV_E, DV_V, DV_N, DV_O});
    ASSERT_STRNE("vyavyivyuvyevyo", send_string_output);
    // 撥音拡張(vy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_Y, DV_SCLN, DV_V, DV_Y, DV_X, DV_V, DV_Y, DV_K, DV_V, DV_Y, DV_J, DV_V, DV_Y, DV_Q});
    ASSERT_STREQ("vyannvyinnvyunnvyennvyonn", send_string_output);
    // 撥音拡張(vh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_H, DV_SCLN, DV_V, DV_H, DV_X, DV_V, DV_H, DV_K, DV_V, DV_H, DV_J, DV_V, DV_H, DV_Q});
    ASSERT_STREQ("vyannvyinnvyunnvyennvyonn", send_string_output);
    // 撥音拡張(vn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_N, DV_SCLN, DV_V, DV_N, DV_X, DV_V, DV_N, DV_K, DV_V, DV_N, DV_J, DV_V, DV_N, DV_Q});
    ASSERT_STRNE("vyannvyinnvyunnvyennvyonn", send_string_output);
    // 二重母音拡張(vy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_Y, DV_QUOT, DV_V, DV_Y, DV_DOT, DV_V, DV_Y, DV_COMM});
    ASSERT_STREQ("vyaivyeivyou", send_string_output);
    // 二重母音拡張(vh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_H, DV_QUOT, DV_V, DV_H, DV_DOT, DV_V, DV_H, DV_COMM});
    ASSERT_STREQ("vyaivyeivyou", send_string_output);
    // 二重母音拡張(vn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_N, DV_QUOT, DV_V, DV_N, DV_DOT, DV_V, DV_N, DV_COMM});
    ASSERT_STRNE("vyaivyeivyou", send_string_output);
}

// ぱ行
TEST(DvorakjpTest, PTest) {
    // 通常(p)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_A, DV_P, DV_I, DV_P, DV_U, DV_P, DV_E, DV_P, DV_O});
    ASSERT_STREQ("papipupepo", send_string_output);
    // 通常(l)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_A, DV_L, DV_I, DV_L, DV_U, DV_L, DV_E, DV_L, DV_O});
    ASSERT_STREQ("papipupepo", send_string_output);
    // 撥音拡張(p)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_SCLN, DV_P, DV_X, DV_P, DV_K, DV_P, DV_J, DV_P, DV_Q});
    ASSERT_STREQ("pannpinnpunnpennponn", send_string_output);
    // 撥音拡張(l)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_SCLN, DV_L, DV_X, DV_L, DV_K, DV_L, DV_J, DV_L, DV_Q});
    ASSERT_STREQ("pannpinnpunnpennponn", send_string_output);
    // 二重母音拡張(p)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_QUOT, DV_P, DV_DOT, DV_P, DV_COMM});
    ASSERT_STREQ("paipeipou", send_string_output);
    // 二重母音拡張(l)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_QUOT, DV_L, DV_DOT, DV_L, DV_COMM});
    ASSERT_STREQ("paipeipou", send_string_output);
}

// ぴゃ行
TEST(DvorakjpTest, PyTest) {
    // 通常(py)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_Y, DV_A, DV_P, DV_Y, DV_I, DV_P, DV_Y, DV_U, DV_P, DV_Y, DV_E, DV_P, DV_Y, DV_O});
    ASSERT_STREQ("pyapyipyupyepyo", send_string_output);
    // 通常(ly)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_Y, DV_A, DV_L, DV_Y, DV_I, DV_L, DV_Y, DV_U, DV_L, DV_Y, DV_E, DV_L, DV_Y, DV_O});
    ASSERT_STREQ("pyapyipyupyepyo", send_string_output);
    // 通常(ph)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_H, DV_A, DV_P, DV_H, DV_I, DV_P, DV_H, DV_U, DV_P, DV_H, DV_E, DV_P, DV_H, DV_O});
    ASSERT_STREQ("pyapyipyupyepyo", send_string_output);
    // 通常(lh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_H, DV_A, DV_L, DV_H, DV_I, DV_L, DV_H, DV_U, DV_L, DV_H, DV_E, DV_L, DV_H, DV_O});
    ASSERT_STREQ("pyapyipyupyepyo", send_string_output);
    // 通常(pn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_N, DV_A, DV_P, DV_N, DV_I, DV_P, DV_N, DV_U, DV_P, DV_N, DV_E, DV_P, DV_N, DV_O});
    ASSERT_STRNE("pyapyipyupyepyo", send_string_output);
    // 通常(ln) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_N, DV_A, DV_L, DV_N, DV_I, DV_L, DV_N, DV_U, DV_L, DV_N, DV_E, DV_L, DV_N, DV_O});
    ASSERT_STRNE("pyapyipyupyepyo", send_string_output);
    // 撥音拡張(py)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_Y, DV_SCLN, DV_P, DV_Y, DV_X, DV_P, DV_Y, DV_K, DV_P, DV_Y, DV_J, DV_P, DV_Y, DV_Q});
    ASSERT_STREQ("pyannpyinnpyunnpyennpyonn", send_string_output);
    // 撥音拡張(ly)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_Y, DV_SCLN, DV_L, DV_Y, DV_X, DV_L, DV_Y, DV_K, DV_L, DV_Y, DV_J, DV_L, DV_Y, DV_Q});
    ASSERT_STREQ("pyannpyinnpyunnpyennpyonn", send_string_output);
    // 撥音拡張(ph)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_H, DV_SCLN, DV_P, DV_H, DV_X, DV_P, DV_H, DV_K, DV_P, DV_H, DV_J, DV_P, DV_H, DV_Q});
    ASSERT_STREQ("pyannpyinnpyunnpyennpyonn", send_string_output);
    // 撥音拡張(lh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_H, DV_SCLN, DV_L, DV_H, DV_X, DV_L, DV_H, DV_K, DV_L, DV_H, DV_J, DV_L, DV_H, DV_Q});
    ASSERT_STREQ("pyannpyinnpyunnpyennpyonn", send_string_output);
    // 撥音拡張(pn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_N, DV_SCLN, DV_P, DV_N, DV_X, DV_P, DV_N, DV_K, DV_P, DV_N, DV_J, DV_P, DV_N, DV_Q});
    ASSERT_STRNE("pyannpyinnpyunnpyennpyonn", send_string_output);
    // 撥音拡張(ln) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_N, DV_SCLN, DV_L, DV_N, DV_X, DV_L, DV_N, DV_K, DV_L, DV_N, DV_J, DV_L, DV_N, DV_Q});
    ASSERT_STRNE("pyannpyinnpyunnpyennpyonn", send_string_output);
    // 二重母音拡張(py)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_Y, DV_QUOT, DV_P, DV_Y, DV_DOT, DV_P, DV_Y, DV_COMM});
    ASSERT_STREQ("pyaipyeipyou", send_string_output);
    // 二重母音拡張(ly)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_Y, DV_QUOT, DV_L, DV_Y, DV_DOT, DV_L, DV_Y, DV_COMM});
    ASSERT_STREQ("pyaipyeipyou", send_string_output);
    // 二重母音拡張(ph)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_H, DV_QUOT, DV_P, DV_H, DV_DOT, DV_P, DV_H, DV_COMM});
    ASSERT_STREQ("pyaipyeipyou", send_string_output);
    // 二重母音拡張(lh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_H, DV_QUOT, DV_L, DV_H, DV_DOT, DV_L, DV_H, DV_COMM});
    ASSERT_STREQ("pyaipyeipyou", send_string_output);
    // 二重母音拡張(pn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_N, DV_QUOT, DV_P, DV_N, DV_DOT, DV_P, DV_N, DV_COMM});
    ASSERT_STRNE("pyaipyeipyou", send_string_output);
    // 二重母音拡張(ln) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_N, DV_QUOT, DV_L, DV_N, DV_DOT, DV_L, DV_N, DV_COMM});
    ASSERT_STRNE("pyaipyeipyou", send_string_output);
}

// ま行
TEST(DvorakjpTest, MTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_A, DV_M, DV_I, DV_M, DV_U, DV_M, DV_E, DV_M, DV_O});
    ASSERT_STREQ("mamimumemo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_SCLN, DV_M, DV_X, DV_M, DV_K, DV_M, DV_J, DV_M, DV_Q});
    ASSERT_STREQ("mannminnmunnmennmonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_QUOT, DV_M, DV_DOT, DV_M, DV_COMM});
    ASSERT_STREQ("maimeimou", send_string_output);
}

// みゃ行
TEST(DvorakjpTest, MyTest) {
    // 通常(my)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_Y, DV_A, DV_M, DV_Y, DV_I, DV_M, DV_Y, DV_U, DV_M, DV_Y, DV_E, DV_M, DV_Y, DV_O});
    ASSERT_STREQ("myamyimyumyemyo", send_string_output);
    // 通常(mh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_H, DV_A, DV_M, DV_H, DV_I, DV_M, DV_H, DV_U, DV_M, DV_H, DV_E, DV_M, DV_H, DV_O});
    ASSERT_STRNE("myamyimyumyemyo", send_string_output);
    // 通常(mn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_N, DV_A, DV_M, DV_N, DV_I, DV_M, DV_N, DV_U, DV_M, DV_N, DV_E, DV_M, DV_N, DV_O});
    ASSERT_STREQ("myamyimyumyemyo", send_string_output);
    // 撥音拡張(my)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_Y, DV_SCLN, DV_M, DV_Y, DV_X, DV_M, DV_Y, DV_K, DV_M, DV_Y, DV_J, DV_M, DV_Y, DV_Q});
    ASSERT_STREQ("myannmyinnmyunnmyennmyonn", send_string_output);
    // 撥音拡張(mh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_H, DV_SCLN, DV_M, DV_H, DV_X, DV_M, DV_H, DV_K, DV_M, DV_H, DV_J, DV_M, DV_H, DV_Q});
    ASSERT_STRNE("myannmyinnmyunnmyennmyonn", send_string_output);
    // 撥音拡張(mn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_N, DV_SCLN, DV_M, DV_N, DV_X, DV_M, DV_N, DV_K, DV_M, DV_N, DV_J, DV_M, DV_N, DV_Q});
    ASSERT_STREQ("myannmyinnmyunnmyennmyonn", send_string_output);
    // 二重母音拡張(my)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_Y, DV_QUOT, DV_M, DV_Y, DV_DOT, DV_M, DV_Y, DV_COMM});
    ASSERT_STREQ("myaimyeimyou", send_string_output);
    // 二重母音拡張(mh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_H, DV_QUOT, DV_M, DV_H, DV_DOT, DV_M, DV_H, DV_COMM});
    ASSERT_STRNE("myaimyeimyou", send_string_output);
    // 二重母音拡張(mn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_N, DV_QUOT, DV_M, DV_N, DV_DOT, DV_M, DV_N, DV_COMM});
    ASSERT_STREQ("myaimyeimyou", send_string_output);
}

// や行
TEST(DvorakjpTest, YTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_A, DV_Y, DV_U, DV_Y, DV_O});
    ASSERT_STREQ("yayuyo", send_string_output);
    // 通常(xy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_Y, DV_A, DV_X, DV_Y, DV_U, DV_X, DV_Y, DV_O});
    ASSERT_STREQ("xyaxyuxyo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_SCLN, DV_Y, DV_K, DV_Y, DV_Q});
    ASSERT_STREQ("yannyunnyonn", send_string_output);
    // 撥音拡張(xy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_Y, DV_SCLN, DV_X, DV_Y, DV_K, DV_X, DV_Y, DV_Q});
    ASSERT_STREQ("xyannxyunnxyonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_QUOT, DV_Y, DV_COMM});
    ASSERT_STREQ("yaiyou", send_string_output);
    // 二重母音拡張(xy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_Y, DV_QUOT, DV_X, DV_Y, DV_COMM});
    ASSERT_STREQ("xyaixyou", send_string_output);
}

// ら行
TEST(DvorakjpTest, RTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_A, DV_R, DV_I, DV_R, DV_U, DV_R, DV_E, DV_R, DV_O});
    ASSERT_STREQ("rarirurero", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_SCLN, DV_R, DV_X, DV_R, DV_K, DV_R, DV_J, DV_R, DV_Q});
    ASSERT_STREQ("rannrinnrunnrennronn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_QUOT, DV_R, DV_DOT, DV_R, DV_COMM});
    ASSERT_STREQ("raireirou", send_string_output);
}

// りゃ行
TEST(DvorakjpTest, RyTest) {
    // 通常(ry)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_Y, DV_A, DV_R, DV_Y, DV_I, DV_R, DV_Y, DV_U, DV_R, DV_Y, DV_E, DV_R, DV_Y, DV_O});
    ASSERT_STREQ("ryaryiryuryeryo", send_string_output);
    // 通常(rh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_H, DV_A, DV_R, DV_H, DV_I, DV_R, DV_H, DV_U, DV_R, DV_H, DV_E, DV_R, DV_H, DV_O});
    ASSERT_STREQ("ryaryiryuryeryo", send_string_output);
    // 通常(rn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_N, DV_A, DV_R, DV_N, DV_I, DV_R, DV_N, DV_U, DV_R, DV_N, DV_E, DV_R, DV_N, DV_O});
    ASSERT_STRNE("ryaryiryuryeryo", send_string_output);
    // 撥音拡張(ry)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_Y, DV_SCLN, DV_R, DV_Y, DV_X, DV_R, DV_Y, DV_K, DV_R, DV_Y, DV_J, DV_R, DV_Y, DV_Q});
    ASSERT_STREQ("ryannryinnryunnryennryonn", send_string_output);
    // 撥音拡張(rh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_H, DV_SCLN, DV_R, DV_H, DV_X, DV_R, DV_H, DV_K, DV_R, DV_H, DV_J, DV_R, DV_H, DV_Q});
    ASSERT_STREQ("ryannryinnryunnryennryonn", send_string_output);
    // 撥音拡張(rn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_N, DV_SCLN, DV_R, DV_N, DV_X, DV_R, DV_N, DV_K, DV_R, DV_N, DV_J, DV_R, DV_N, DV_Q});
    ASSERT_STRNE("ryannryinnryunnryennryonn", send_string_output);
    // 二重母音拡張(ry)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_Y, DV_QUOT, DV_R, DV_Y, DV_DOT, DV_R, DV_Y, DV_COMM});
    ASSERT_STREQ("ryairyeiryou", send_string_output);
    // 二重母音拡張(rh)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_H, DV_QUOT, DV_R, DV_H, DV_DOT, DV_R, DV_H, DV_COMM});
    ASSERT_STREQ("ryairyeiryou", send_string_output);
    // 二重母音拡張(rn) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_N, DV_QUOT, DV_R, DV_N, DV_DOT, DV_R, DV_N, DV_COMM});
    ASSERT_STRNE("ryairyeiryou", send_string_output);
}

// わ行
TEST(DvorakjpTest, WTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_A, DV_W, DV_O});
    ASSERT_STREQ("wawo", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_SCLN, DV_W, DV_Q});
    ASSERT_STREQ("wannwonn", send_string_output);
    // 二重母音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_QUOT, DV_W, DV_COMM});
    ASSERT_STREQ("waiwou", send_string_output);

    // 通常(wy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_Y, DV_I, DV_W, DV_Y, DV_E});
    ASSERT_STREQ("wyiwye", send_string_output);
    // 通常(wh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_H, DV_I, DV_W, DV_H, DV_E});
    ASSERT_STRNE("wyiwye", send_string_output);
    // 通常(wn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_N, DV_I, DV_W, DV_N, DV_E});
    ASSERT_STREQ("wyiwye", send_string_output);
    // 撥音拡張(wy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_Y, DV_X, DV_W, DV_Y, DV_J});
    ASSERT_STREQ("wyinnwyenn", send_string_output);
    // 撥音拡張(wh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_H, DV_X, DV_W, DV_H, DV_J});
    ASSERT_STRNE("wyinnwyenn", send_string_output);
    // 撥音拡張(wn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_N, DV_X, DV_W, DV_N, DV_J});
    ASSERT_STREQ("wyinnwyenn", send_string_output);
    // 二重母音拡張(wy)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_Y, DV_DOT});
    ASSERT_STREQ("wyei", send_string_output);
    // 二重母音拡張(wh) ※変換しない
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_H, DV_DOT});
    ASSERT_STRNE("wyei", send_string_output);
    // 二重母音拡張(wn)
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_N, DV_DOT});
    ASSERT_STREQ("wyei", send_string_output);
}

// っ, ん
TEST(DvorakjpTest, XtuTest) {
    // 通常
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_T, DV_U});
    ASSERT_STREQ("xtu", send_string_output);
    // 撥音拡張
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_X, DV_T, DV_K});
    ASSERT_STREQ("xtunn", send_string_output);
    // 各子音
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_K, DV_K, DV_QUOT});
    ASSERT_STREQ("kkai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_C, DV_C, DV_QUOT});
    ASSERT_STREQ("kkai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Q, DV_Q, DV_QUOT});
    ASSERT_STREQ("qqai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_G, DV_G, DV_QUOT});
    ASSERT_STREQ("ggai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_S, DV_S, DV_QUOT});
    ASSERT_STREQ("ssai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Z, DV_Z, DV_QUOT});
    ASSERT_STREQ("zzai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_T, DV_T, DV_QUOT});
    ASSERT_STREQ("ttai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_D, DV_D, DV_QUOT});
    ASSERT_STREQ("ddai", send_string_output);
    // ん
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_N, DV_N, DV_QUOT});
    ASSERT_STRNE("nnai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_H, DV_H, DV_QUOT});
    ASSERT_STREQ("hhai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_B, DV_B, DV_QUOT});
    ASSERT_STREQ("bbai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_V, DV_V, DV_QUOT});
    ASSERT_STREQ("vvai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_P, DV_P, DV_QUOT});
    ASSERT_STREQ("ppai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_L, DV_L, DV_QUOT});
    ASSERT_STREQ("ppai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_M, DV_M, DV_QUOT});
    ASSERT_STREQ("mmai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_Y, DV_Y, DV_QUOT});
    ASSERT_STREQ("yyai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_R, DV_R, DV_QUOT});
    ASSERT_STREQ("rrai", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input({DV_W, DV_W, DV_QUOT});
    ASSERT_STREQ("wwai", send_string_output);
}

// TODO: 下記のテストが足りない
// *n *y 
// wh k [kqgsztdhx]w(xwa) ts x[ck](xca xka xce xke) xt(xtu)
// ツァ行(ts)
// ヵ,ヶ,っ x[ck](xca xka xce xke) xt(xtu)
// テャ,デャ,ウァ行([tdw]h)
// クァ,グァ,トァ,ドァ,ファ[cgtdh]w
// クァ,スァ,ズァ,ヮ[kqszx]w(xwa)
