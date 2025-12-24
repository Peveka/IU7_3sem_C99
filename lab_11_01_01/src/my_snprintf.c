#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "string_print_functions.h"

static void handle_specifier(char specifier, va_list *args, char *str, size_t n, int *count)
{
    switch (specifier) 
    {
        case 'c': 
            print_char_to_string(str, (char)va_arg(*args, int), n, count);
            break;
        case 's': 
            print_string_to_string(str, va_arg(*args, char *), n, count);
            break;
        case 'd': 
        case 'i': 
            print_num_to_string(str, va_arg(*args, int), n, count);
            break;
        case 'x': 
            print_hex_to_string(str, va_arg(*args, unsigned int), n, count);
            break;
        case 'o': 
            print_oct_to_string(str, va_arg(*args, unsigned int), n, count);
            break;
        default:
            print_char_to_string(str, '%', n, count);
            print_char_to_string(str, specifier, n, count);
            break;
    }
}

int my_snprintf(char *restrict str, size_t n, const char *restrict format, ...)
{
    if (format == NULL)
        return -1;

    va_list args;
    va_start(args, format);
    int printed_elems_count = 0;
    char *output_buffer = (n == 0) ? NULL : str;
    size_t output_size = (n == 0) ? 0 : n;
    
    for (int i = 0; format[i] != '\0'; i++) 
    {
        if (format[i] == '%' && format[i + 1] != '\0') 
            handle_specifier(format[++i], &args, output_buffer, output_size, &printed_elems_count);
        else
            print_char_to_string(output_buffer, format[i], output_size, &printed_elems_count);
    }

    va_end(args);
    
    if (str && n > 0) 
        str[printed_elems_count < n ? printed_elems_count : n - 1] = '\0';
    
    return printed_elems_count;
}