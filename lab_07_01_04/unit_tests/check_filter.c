#include <check.h>
#include <malloc.h>
#include "filter.h"
#include "errors.h"
#include "check_filter.h"

START_TEST(key_empty_arr)
{
    int arr[] = {0, 1};
    int *pb_s = arr;
    int *pe_s = pb_s;
    int *pb_d;
    int *pe_d;
    int rc;

    rc = key(pb_s, pe_s, &pb_d, &pe_d);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_null_src)
{
    int arr[] = {0, 1};
    int *pb_s = arr;
    int *pe_s = NULL;
    int *pb_d; 
    int *pe_d;
    int rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_null_dst_start)
{
    int arr[2] = {0, 1};
    int *pb_s = arr;
    int *pe_s = arr + 2;
    int *pe_d;
    int rc = key(pb_s, pe_s, NULL, &pe_d);

    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_null_dst_end)
{
    int arr[2] = {0, 1};
    int *pb_s = arr;
    int *pe_s = arr + 2;
    int *ps_d = NULL;
    int rc;

    rc = key(pb_s, pe_s, &ps_d, NULL);
    ck_assert_int_eq(rc, ERROR_INVALID_DATA);
}
END_TEST

START_TEST(key_empty_out_arr)
{
    int arr[] = {1, 1, 1}; // Avg 1.0
    int *pb_s = arr;
    int *pe_s = arr + 3;
    int *pb_d, *pe_d;
    int rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, ERROR_EMPTY_RESULT);
}
END_TEST

START_TEST(key_normal_case_first_test)
{
    int arr[] = {5, 2, 8, 1, 9}; // Avg 5
    int *pb_s = arr;
    int *pe_s = arr + 5;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {8, 9};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 2);
    ck_assert_mem_eq(pb_d, expected, sizeof(expected));

    free(pb_d);
}
END_TEST

START_TEST(key_normal_case_second_test)
{
    int arr[] = {100, 200, 300, 400}; // Avg: 250
    int *pb_s = arr;
    int *pe_s = arr + 4;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {300, 400};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 2);
    ck_assert_mem_eq(pb_d, expected, sizeof(expected));

    free(pb_d);
}
END_TEST

START_TEST(key_normal_case_third_test)
{
    int arr[] = {1, 2, 3, 4}; // AVG: 2.5
    int *pb_s = arr;
    int *pe_s = arr + 4;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {3, 4};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 2);
    ck_assert_mem_eq(pb_d, expected, sizeof(expected));

    free(pb_d);
}
END_TEST


START_TEST(key_negative_numbers)
{
    int arr[] = {-10, -5, 0, 5, 10}; // AVG: 0
    int *pb_s = arr;
    int *pe_s = arr + 5;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {5, 10};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 2);
    ck_assert_mem_eq(pb_d, expected, sizeof(expected));

    free(pb_d);
}
END_TEST

START_TEST(key_large_range)
{
    int arr[] = {1, 1000, 2, 2000, 3, 3000}; // AVG 1334.(3)
    int *pb_s = arr;
    int *pe_s = arr + 6;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {2000, 3000};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 2);
    ck_assert_mem_eq(pb_d, expected, sizeof(expected));

    free(pb_d);
}
END_TEST

START_TEST(key_two_elements)
{
    int arr[] = {10, 20}; // AVG: 15
    int *pb_s = arr;
    int *pe_s = arr + 2;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {20};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 1);
    ck_assert_int_eq(pb_d[0], expected[0]);

    free(pb_d);
}
END_TEST

START_TEST(key_only_one_less_then_avg)
{
    int arr[] = {1, 10, 10, 10}; // AVG: 7.75
    int *pb_s = arr;
    int *pe_s = arr + 4;
    int *pb_d, *pe_d;
    int rc;
    int expected[] = {10, 10, 10};

    rc = key(pb_s, pe_s, &pb_d, &pe_d);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(pe_d - pb_d, 3);
    ck_assert_mem_eq(pb_d, expected, sizeof(expected));

    free(pb_d);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("key");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, key_normal_case_first_test);
    tcase_add_test(tc_pos, key_normal_case_second_test);
    tcase_add_test(tc_pos, key_normal_case_third_test);
    tcase_add_test(tc_pos, key_negative_numbers);
    tcase_add_test(tc_pos, key_large_range);
    tcase_add_test(tc_pos, key_two_elements);
    tcase_add_test(tc_pos, key_only_one_less_then_avg);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, key_empty_arr);
    tcase_add_test(tc_neg, key_null_src);
    tcase_add_test(tc_neg, key_null_dst_start);
    tcase_add_test(tc_neg, key_null_dst_end);
    tcase_add_test(tc_neg, key_empty_out_arr);
    suite_add_tcase(s, tc_neg);

    return s;
}