#include "mock.h"

#define X_A_2_C 0x5d // 61(a) - 04(X_A)

char send_string_output[100];
unsigned short int send_string_output_index = 0;

void send_string(const char *string) {
    send_string_output[send_string_output_index++] = string[2] + X_A_2_C;
}
