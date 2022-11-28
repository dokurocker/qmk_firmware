#include "gtest/gtest.h"

extern "C" {
#include "dvorakjp/dvorakjp.h"
#include "mock.h"
#include "print.h"
}

#define INPUT_END DVORAK_NEW_SAFE_RANGE

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
    }

    static void Input(uint16_t* keycodes) {
        char dvorakMap[] = "1234567890[]',.pyfgcrl/=aoeuidhtns-;qjkxbmwvz";
        do {
            if (!dvorakjp(*keycodes, 0)) {
                // send_string_outputに文字入らないので入れる
                send_string_output[send_string_output_index++] = dvorakMap[*keycodes - DV_1];
            }
        } while (*(++keycodes) != INPUT_END);
    }
};

TEST(DvorakjpTest, UnkoTest) {
    uint16_t keycodes[] = {DV_U, DV_N, DV_C, DV_O, INPUT_END};
    uint16_t keycodes2[] = {DV_U, DV_N, DV_N, DV_C, DV_O, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("unko", send_string_output);
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes2);
    ASSERT_STREQ("unnko", send_string_output);
}

TEST(DvorakjpTest, UntinTest) {
    uint16_t keycodes[] = {DV_U, DV_N, DV_T, DV_X, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("untinn", send_string_output);
}

TEST(DvorakjpTest, TintinTest) {
    uint16_t keycodes[] = {DV_T, DV_X, DV_T, DV_X, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("tinntinn", send_string_output);
}

TEST(DvorakjpTest, NakataTest) {
    uint16_t keycodes[] = {DV_N, DV_A, DV_C, DV_A, DV_T, DV_A, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("nakata", send_string_output);
}

TEST(DvorakjpTest, NogusoTest) {
    uint16_t keycodes[] = {DV_N, DV_O, DV_G, DV_U, DV_S, DV_O, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("noguso", send_string_output);
}

TEST(DvorakjpTest, NingenTest) {
    uint16_t keycodes[] = {DV_N, DV_X, DV_G, DV_J, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("ninngenn", send_string_output);
}

TEST(DvorakjpTest, PaMinsThiMinsTest) {
    uint16_t keycodes[] = {DV_P, DV_A, DV_MINS, DV_T, DV_H, DV_I, DV_MINS, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("pa-thi-", send_string_output);
}

TEST(DvorakjpTest, DaisougenTest) {
    uint16_t keycodes[] = {DV_D, DV_QUOT, DV_S, DV_COMM, DV_G, DV_J, INPUT_END};
    DvorakjpTest::ClearOutput();
    DvorakjpTest::Input(keycodes);
    ASSERT_STREQ("daisougenn", send_string_output);
}
