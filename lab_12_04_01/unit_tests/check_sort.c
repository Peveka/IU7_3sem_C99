#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "check_sort.h"

START_TEST(mysort_normal_int)
{
    int arr[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};

    mysort(arr, 5, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_already_sorted)
{
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};

    mysort(arr, 5, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_reverse_sorted)
{
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};

    mysort(arr, 5, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_all_equal)
{
    int arr[] = {3, 3, 3, 3};
    int expected[] = {3, 3, 3, 3};

    mysort(arr, 4, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_single_element)
{
    int arr[] = {42};
    int expected[] = {42};

    mysort(arr, 1, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_empty)
{
    int arr[1];
    mysort(arr, 0, sizeof(int), cmp_int);
    ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(mysort_negative_numbers)
{
    int arr[] = {-5, -1, -10, 0, 3};
    int expected[] = {-10, -5, -1, 0, 3};

    mysort(arr, 5, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_mixed_numbers)
{
    int arr[] = {0, -2, 7, -8, 4};
    int expected[] = {-8, -2, 0, 4, 7};

    mysort(arr, 5, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_duplicates)
{
    int arr[] = {4, 2, 4, 2, 4};
    int expected[] = {2, 2, 4, 4, 4};

    mysort(arr, 5, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

START_TEST(mysort_two_elements)
{
    int arr[] = {10, 1};
    int expected[] = {1, 10};

    mysort(arr, 2, sizeof(int), cmp_int);

    ck_assert_mem_eq(arr, expected, sizeof(expected));
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s = suite_create("mysort");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, mysort_normal_int);
    tcase_add_test(tc_core, mysort_already_sorted);
    tcase_add_test(tc_core, mysort_reverse_sorted);
    tcase_add_test(tc_core, mysort_all_equal);
    tcase_add_test(tc_core, mysort_single_element);
    tcase_add_test(tc_core, mysort_empty);
    tcase_add_test(tc_core, mysort_negative_numbers);
    tcase_add_test(tc_core, mysort_mixed_numbers);
    tcase_add_test(tc_core, mysort_duplicates);
    tcase_add_test(tc_core, mysort_two_elements);

    suite_add_tcase(s, tc_core);

    return s;
}