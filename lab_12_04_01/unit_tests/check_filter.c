#include <check.h>
#include "filter.h"
#include "errors.h"
#include "memory.h"
#include "check_filter.h"

START_TEST(key_empty_arr)
{
    int src[] = {1, 2};
    int *pb_src = src;
    int *pe_src = src;
    int *dst_buffer = NULL;
    int *pe_dst = NULL;

    error_t rc = key(pb_src, pe_src, dst_buffer, &pe_dst);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_null_src)
{
    int *dst_buffer = NULL;
    int *pe_dst = NULL;

    error_t rc = key(NULL, NULL, dst_buffer, &pe_dst);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_null_dst_buffer)
{
    int src[] = {1, 2, 3};
    int *pe_dst = NULL;

    error_t rc = key(src, src + 3, NULL, &pe_dst);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_null_dst_end)
{
    int src[] = {1, 2, 3};
    int dst_buffer[3];

    error_t rc = key(src, src + 3, dst_buffer, NULL);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_normal_case)
{
    int src[] = {1, 2, 3, 4, 5};
    int expected[] = {4, 5};
    int *dst_buffer = NULL;
    int *dst_end = NULL;
    error_t rc;

    rc = allocate_memory_with_check(sizeof(src), (void **)&dst_buffer);
    ck_assert_int_eq(rc, OK);

    rc = key(src, src + 5, dst_buffer, &dst_end);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(dst_end - dst_buffer, 2);
    ck_assert_mem_eq(dst_buffer, expected, 2 * sizeof(int));

    free_memory((void **)&dst_buffer);
}
END_TEST

START_TEST(key_all_less_than_avg)
{
    int src[] = {1, 1, 1};
    int *dst_buffer = NULL;
    int *dst_end = NULL;
    error_t rc;

    rc = allocate_memory_with_check(sizeof(src), (void **)&dst_buffer);
    ck_assert_int_eq(rc, OK);

    rc = key(src, src + 3, dst_buffer, &dst_end);
    ck_assert_int_eq(rc, ERROR_EMPTY_RESULT);

    free_memory((void **)&dst_buffer);
}
END_TEST

START_TEST(key_negative_numbers)
{
    int src[] = {-5, -3, -1, 0};
    int expected[] = {-1, 0};
    int *dst_buffer = NULL;
    int *dst_end = NULL;
    error_t rc;

    rc = allocate_memory_with_check(sizeof(src), (void **)&dst_buffer);
    ck_assert_int_eq(rc, OK);

    rc = key(src, src + 4, dst_buffer, &dst_end);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(dst_end - dst_buffer, 2);
    ck_assert_mem_eq(dst_buffer, expected, sizeof(expected));

    free_memory((void **)&dst_buffer);
}
END_TEST

START_TEST(key_single_element_greater)
{
    int src[] = {10};
    int expected[] = {10};
    int *dst_buffer = NULL;
    int *dst_end = NULL;
    error_t rc;

    rc = allocate_memory_with_check(sizeof(src), (void **)&dst_buffer);
    ck_assert_int_eq(rc, OK);

    rc = key(src, src + 1, dst_buffer, &dst_end);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(dst_end - dst_buffer, 1);
    ck_assert_mem_eq(dst_buffer, expected, sizeof(expected));

    free_memory((void **)&dst_buffer);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s = suite_create("key_filter");
    TCase *tc_pos = tcase_create("positive");
    TCase *tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, key_normal_case);
    tcase_add_test(tc_pos, key_all_less_than_avg);
    tcase_add_test(tc_pos, key_negative_numbers);
    tcase_add_test(tc_pos, key_single_element_greater);

    tcase_add_test(tc_neg, key_empty_arr);
    tcase_add_test(tc_neg, key_null_src);
    tcase_add_test(tc_neg, key_null_dst_buffer);
    tcase_add_test(tc_neg, key_null_dst_end);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}