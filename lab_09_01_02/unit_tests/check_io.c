#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "io.h"
#include "errors.h"

START_TEST(test_file_read_line_null_args)
{
    char buffer[100];
    error_t rc = file_read_line(NULL, buffer, sizeof(buffer));
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
    
    FILE *file = fopen("test.txt", "w");
    ck_assert_ptr_nonnull(file);
    
    rc = file_read_line(file, NULL, sizeof(buffer));
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
    
    fclose(file);
    
    file = fopen("test.txt", "w");
    ck_assert_ptr_nonnull(file);
    
    rc = file_read_line(file, buffer, 0);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
    
    fclose(file);
    remove("test.txt");
}
END_TEST

START_TEST(test_strip_string_basic)
{
    FILE *file = fopen("test_temp.txt", "w");
    ck_assert_ptr_nonnull(file);
    
    fputs("line1\n", file);
    fputs("line2\r\n", file);
    fputs("line3", file);
    fclose(file);
    
    file = fopen("test_temp.txt", "r");
    ck_assert_ptr_nonnull(file);
    
    char buffer[100];
    
    error_t rc = file_read_line(file, buffer, sizeof(buffer));
    ck_assert_int_eq(rc, OK);
    ck_assert_str_eq(buffer, "line1");
    
    rc = file_read_line(file, buffer, sizeof(buffer));
    ck_assert_int_eq(rc, OK);
    ck_assert_str_eq(buffer, "line2");
    
    rc = file_read_line(file, buffer, sizeof(buffer));
    ck_assert_int_eq(rc, OK);
    ck_assert_str_eq(buffer, "line3");
    
    fclose(file);
    remove("test_temp.txt");
}
END_TEST

START_TEST(test_file_read_line_eof)
{
    FILE *file = fopen("empty.txt", "w");
    ck_assert_ptr_nonnull(file);
    fclose(file);
    
    file = fopen("empty.txt", "r");
    ck_assert_ptr_nonnull(file);
    
    char buffer[100];
    error_t rc = file_read_line(file, buffer, sizeof(buffer));
    ck_assert_int_eq(rc, ERROR_FILE_READ);
    
    fclose(file);
    remove("empty.txt");
}
END_TEST

Suite *io_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("IO");
    
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_file_read_line_null_args);
    tcase_add_test(tc_core, test_strip_string_basic);
    tcase_add_test(tc_core, test_file_read_line_eof);
    
    suite_add_tcase(s, tc_core);
    
    return s;
}