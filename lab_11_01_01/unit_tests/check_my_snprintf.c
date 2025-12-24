#include <check.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my_snprintf.h"

// Тест для %c спецификатора
START_TEST(test_char_specifier)
{
    char buffer[100];
    char std_buffer[100];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Char: %c", 'A');
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Char: %c", 'A');
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

// Тест для %s спецификатора
START_TEST(test_string_specifier)
{
    char buffer[100];
    char std_buffer[100];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Hello %s!", "World");
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Hello %s!", "World");
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

// Тест для %d спецификатора
START_TEST(test_decimal_specifier)
{
    char buffer[100];
    char std_buffer[100];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Number: %d", 123);
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Number: %d", 123);
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

// Тест для %o спецификатора
START_TEST(test_octal_specifier)
{
    char buffer[100];
    char std_buffer[100];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Octal: %o", 8);
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Octal: %o", 8);
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

// Тест для %x спецификатора
START_TEST(test_hex_specifier)
{
    char buffer[100];
    char std_buffer[100];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Hex: %x", 10);
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Hex: %x", 10);
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

// Тест смешанных спецификаторо
START_TEST(test_mixed_specifiers)
{
    char buffer[200];
    char std_buffer[200];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Char: %c, Str: %s, Dec: %d", 'X', "test", 123);
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Char: %c, Str: %s, Dec: %d", 'X', "test", 123);
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

// Тест без спецификаторов
START_TEST(test_no_specifiers)
{
    char buffer[100];
    char std_buffer[100];
    int my_len, std_len;
    
    my_len = my_snprintf(buffer, sizeof(buffer), "Just a regular string");
    std_len = snprintf(std_buffer, sizeof(std_buffer), "Just a regular string");
    ck_assert_int_eq(my_len, std_len);
    ck_assert_str_eq(buffer, std_buffer);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("my_snprintf");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_char_specifier);
    tcase_add_test(tc_core, test_string_specifier);
    tcase_add_test(tc_core, test_decimal_specifier);
    tcase_add_test(tc_core, test_octal_specifier);
    tcase_add_test(tc_core, test_hex_specifier);
    tcase_add_test(tc_core, test_mixed_specifiers);
    tcase_add_test(tc_core, test_no_specifiers);

    suite_add_tcase(s, tc_core);

    return s;
}