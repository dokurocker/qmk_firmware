#include <stdbool.h>
#include "mock.h"

#define X_A_2_C 0x5d // 61(a) - 04(X_A)

char send_string_output[100];
unsigned short int send_string_output_index = 0;
bool is_shifted = false;

void send_string(const char *string) {
    if (string[2] <= 0x1d) {
        // <= Z
        send_string_output[send_string_output_index++] = string[2] + X_A_2_C;
    } else if (string[2] == 0x2d) {
        // == -
        send_string_output[send_string_output_index++] = '-';
    } else if (string[2] == 0x38) {
        // == /
        send_string_output[send_string_output_index++] = '/';
    } else if (string[2] == 0x35) {
        // == `
        send_string_output[send_string_output_index++] = '`';
    }
}
