#ifndef PRINT_F__
#define PRINT_F__

void print_char_to_string(char *restrict string, char char_to_print, size_t n, int *printed_count);
void print_string_to_string(char *restrict string, const char *string_to_print, size_t n, int *printed_count);
void print_oct_to_string(char *restrict string, int num_to_print, size_t n, int *printed_count);
void print_num_to_string(char *restrict string, int num_to_print, size_t n, int *printed_count);
void print_hex_to_string(char *restrict string, int num_to_print, size_t n, int *printed_count);

#endif