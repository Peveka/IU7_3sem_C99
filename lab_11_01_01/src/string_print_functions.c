#include <stdio.h>
#include "notation_translators.h"

void print_char_to_string(char *restrict string, char char_to_print, size_t n, int *printed_count)
{
    if (n > 0 && *printed_count < n - 1)
        *(string + *printed_count) = char_to_print;
    (*printed_count)++;
}

void print_string_to_string(char *restrict string, const char *string_to_print, size_t n, int *printed_count)
{
    if (!string_to_print)
        string_to_print = "(null)";
    for (size_t i = 0; *(string_to_print + i) != '\0'; i++)
        print_char_to_string(string, *(string_to_print + i), n, printed_count);
}

void print_num_to_string(char *restrict string, int num_to_print, size_t n, int *printed_count)
{
    char buffer[32];
    int_to_string(num_to_print, buffer, sizeof(buffer));
    print_string_to_string(string, buffer, n, printed_count);
}

void print_oct_to_string(char *restrict string, int num_to_print, size_t n, int *printed_count)
{
    char buffer[32];
    int_to_oct_string(num_to_print, buffer, sizeof(buffer));
    print_string_to_string(string, buffer, n, printed_count);
}

void print_hex_to_string(char *restrict string, int num_to_print, size_t n, int *printed_count)
{
    char buffer[32];
    int_to_hex_string(num_to_print, buffer, sizeof(buffer));
    print_string_to_string(string, buffer, n, printed_count);
}