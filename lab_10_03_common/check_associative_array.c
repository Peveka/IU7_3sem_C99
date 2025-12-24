#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "associative_array.h"

START_TEST(test_assoc_array_create_destroy)
{
    assoc_array_t arr = assoc_array_create();
    ck_assert_ptr_nonnull(arr);
    
    assoc_array_destroy(&arr);
    ck_assert_ptr_null(arr);
}
END_TEST

START_TEST(test_assoc_array_insert_find)
{
    assoc_array_t arr = assoc_array_create();
    int value = 42;
    int *found_value = NULL;
    
    assoc_array_error_t rc = assoc_array_insert(arr, "key1", value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_find(arr, "key1", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(found_value);
    ck_assert_int_eq(*found_value, value);

    rc = assoc_array_find(arr, "nonexistent", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_insert_duplicate)
{
    assoc_array_t arr = assoc_array_create();
    
    assoc_array_error_t rc = assoc_array_insert(arr, "key1", 10);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    rc = assoc_array_insert(arr, "key1", 20);
    ck_assert_int_eq(rc, ASSOC_ARRAY_KEY_EXISTS);
    
    int *found_value = NULL;
    rc = assoc_array_find(arr, "key1", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*found_value, 10);
    
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_remove)
{
    assoc_array_t arr = assoc_array_create();
    
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);
    
    assoc_array_error_t rc = assoc_array_remove(arr, "key2");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    int *found_value = NULL;
    rc = assoc_array_find(arr, "key2", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    rc = assoc_array_find(arr, "key1", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*found_value, 10);
    
    rc = assoc_array_find(arr, "key3", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*found_value, 30);
    
    rc = assoc_array_remove(arr, "nonexistent");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_clear)
{
    assoc_array_t arr = assoc_array_create();
    
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);
    
    assoc_array_error_t rc = assoc_array_clear(arr);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    
    int *found_value = NULL;
    rc = assoc_array_find(arr, "key1", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    rc = assoc_array_find(arr, "key2", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    rc = assoc_array_find(arr, "key3", &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_min_max)
{
    assoc_array_t arr = assoc_array_create();
    int *found_value = NULL;
    
    assoc_array_error_t rc = assoc_array_min(arr, &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    rc = assoc_array_max(arr, &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_insert(arr, "banana", 3);
    assoc_array_insert(arr, "apple", 1);
    assoc_array_insert(arr, "cherry", 2);
    
    rc = assoc_array_min(arr, &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(found_value);
    
    rc = assoc_array_max(arr, &found_value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_ptr_nonnull(found_value);
    
    assoc_array_destroy(&arr);
}
END_TEST

void sum_action(const char *key, int *num, void *param)
{
        (void)key;
        int *sum_ptr = (int *)param;
        *sum_ptr += *num;
}

START_TEST(test_assoc_array_each)
{
    assoc_array_t arr = assoc_array_create();
    
    assoc_array_insert(arr, "key1", 10);
    assoc_array_insert(arr, "key2", 20);
    assoc_array_insert(arr, "key3", 30);
    
    int sum = 0;
    
    assoc_array_error_t rc = assoc_array_each(arr, sum_action, &sum);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(sum, 60);
    
    assoc_array_destroy(&arr);
}
END_TEST

START_TEST(test_assoc_array_invalid_params)
{
    assoc_array_t arr = assoc_array_create();
    int *num_ptr = NULL;
    
    ck_assert_int_eq(assoc_array_insert(NULL, "key", 1), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_insert(arr, NULL, 1), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_insert(arr, "", 1), ASSOC_ARRAY_INVALID_PARAM);
    
    ck_assert_int_eq(assoc_array_find(NULL, "key", &num_ptr), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_find(arr, NULL, &num_ptr), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_find(arr, "key", NULL), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_find(arr, "", &num_ptr), ASSOC_ARRAY_INVALID_PARAM);
    
    ck_assert_int_eq(assoc_array_remove(NULL, "key"), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_remove(arr, NULL), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_remove(arr, ""), ASSOC_ARRAY_INVALID_PARAM);
    
    ck_assert_int_eq(assoc_array_clear(NULL), ASSOC_ARRAY_INVALID_PARAM);
    
    ck_assert_int_eq(assoc_array_min(NULL, &num_ptr), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_min(arr, NULL), ASSOC_ARRAY_INVALID_PARAM);
    
    ck_assert_int_eq(assoc_array_max(NULL, &num_ptr), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_max(arr, NULL), ASSOC_ARRAY_INVALID_PARAM);
    
    ck_assert_int_eq(assoc_array_each(NULL, NULL, NULL), ASSOC_ARRAY_INVALID_PARAM);
    ck_assert_int_eq(assoc_array_each(arr, NULL, NULL), ASSOC_ARRAY_INVALID_PARAM);
    
    assoc_array_destroy(&arr);
    
    assoc_array_t null_arr = NULL;
    assoc_array_destroy(&null_arr);
}
END_TEST

START_TEST(test_assoc_array_multiple_operations)
{
    assoc_array_t arr = assoc_array_create();
    
    for (int i = 0; i < 10; i++) {
        char key[10];
        snprintf(key, sizeof(key), "key%d", i);
        assoc_array_error_t rc = assoc_array_insert(arr, key, i * 10);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    }
    
    for (int i = 0; i < 10; i++) {
        char key[10];
        snprintf(key, sizeof(key), "key%d", i);
        int *found_value = NULL;
        assoc_array_error_t rc = assoc_array_find(arr, key, &found_value);
        ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
        ck_assert_int_eq(*found_value, i * 10);
    }
    
    assoc_array_remove(arr, "key2");
    assoc_array_remove(arr, "key5");
    assoc_array_remove(arr, "key8");
    
    int *found_value = NULL;
    ck_assert_int_eq(assoc_array_find(arr, "key2", &found_value), ASSOC_ARRAY_NOT_FOUND);
    ck_assert_int_eq(assoc_array_find(arr, "key5", &found_value), ASSOC_ARRAY_NOT_FOUND);
    ck_assert_int_eq(assoc_array_find(arr, "key8", &found_value), ASSOC_ARRAY_NOT_FOUND);
    
    ck_assert_int_eq(assoc_array_find(arr, "key0", &found_value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*found_value, 0);
    
    ck_assert_int_eq(assoc_array_find(arr, "key9", &found_value), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*found_value, 90);
    
    assoc_array_destroy(&arr);
}
END_TEST

Suite *assoc_array_suite(void)
{
    Suite *s;
    TCase *tc_core, *tc_errors;

    s = suite_create("Associative Array");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_assoc_array_create_destroy);
    tcase_add_test(tc_core, test_assoc_array_insert_find);
    tcase_add_test(tc_core, test_assoc_array_insert_duplicate);
    tcase_add_test(tc_core, test_assoc_array_remove);
    tcase_add_test(tc_core, test_assoc_array_clear);
    tcase_add_test(tc_core, test_assoc_array_min_max);
    tcase_add_test(tc_core, test_assoc_array_each);
    tcase_add_test(tc_core, test_assoc_array_multiple_operations);
    suite_add_tcase(s, tc_core);

    tc_errors = tcase_create("Errors");
    tcase_add_test(tc_errors, test_assoc_array_invalid_params);
    suite_add_tcase(s, tc_errors);

    return s;
}