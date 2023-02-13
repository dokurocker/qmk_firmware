#pragma once

extern char send_string_output[100];
extern unsigned short int send_string_output_index;
extern bool is_shifted;

void send_string(const char *string);