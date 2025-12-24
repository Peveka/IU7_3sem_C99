#include <check.h>
#include <stdlib.h>
#include "matrix_operations.h"
#include "matrix_memory_handle.h"
#include "check_matrix_operations.h"

START_TEST(test_matrix_addition_null_first)
{
    matrix_t matrix_B = {2, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_addition(NULL, &matrix_B, &res_matrix);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_matrix_addition_null_second)
{
    matrix_t matrix_A = {2, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_addition(&matrix_A, NULL, &res_matrix);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_matrix_addition_null_result)
{
    matrix_t matrix_A = {2, 2, NULL};
    matrix_t matrix_B = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_addition(&matrix_A, &matrix_B, NULL);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_matrix_addition_invalid_dimensions)
{
    matrix_t matrix_A = {2, 3, NULL};
    matrix_t matrix_B = {3, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    matrix_alloc(&matrix_A.matrix_data, 2, 3);
    matrix_alloc(&matrix_B.matrix_data, 3, 2);
    matrix_alloc(&res_matrix.matrix_data, 2, 2);
    
    rc = matrix_addition(&matrix_A, &matrix_B, &res_matrix);
    ck_assert_int_eq(rc, ERR_MATRIX_DIMENSIONS);
    
    free_matrix(&matrix_A.matrix_data, matrix_A.rows);
    free_matrix(&matrix_B.matrix_data, matrix_B.rows);
    free_matrix(&res_matrix.matrix_data, res_matrix.rows);
}
END_TEST

START_TEST(test_matrix_addition_normal_case)
{
    matrix_t matrix_A = {2, 2, NULL};
    matrix_t matrix_B = {2, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    matrix_alloc(&matrix_A.matrix_data, 2, 2);
    matrix_alloc(&matrix_B.matrix_data, 2, 2);
    matrix_alloc(&res_matrix.matrix_data, 2, 2);
    
    matrix_A.matrix_data[0][0] = 1.0; matrix_A.matrix_data[0][1] = 2.0;
    matrix_A.matrix_data[1][0] = 3.0; matrix_A.matrix_data[1][1] = 4.0;
    
    matrix_B.matrix_data[0][0] = 5.0; matrix_B.matrix_data[0][1] = 6.0;
    matrix_B.matrix_data[1][0] = 7.0; matrix_B.matrix_data[1][1] = 8.0;
    
    rc = matrix_addition(&matrix_A, &matrix_B, &res_matrix);
    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq(res_matrix.matrix_data[0][0], 6.0);
    ck_assert_double_eq(res_matrix.matrix_data[0][1], 8.0);
    ck_assert_double_eq(res_matrix.matrix_data[1][0], 10.0);
    ck_assert_double_eq(res_matrix.matrix_data[1][1], 12.0);
    
    free_matrix(&matrix_A.matrix_data, matrix_A.rows);
    free_matrix(&matrix_B.matrix_data, matrix_B.rows);
    free_matrix(&res_matrix.matrix_data, res_matrix.rows);
}
END_TEST

START_TEST(test_matrix_multiply_null_first)
{
    matrix_t matrix_B = {2, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_multiply(NULL, &matrix_B, &res_matrix);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_matrix_multiply_null_second)
{
    matrix_t matrix_A = {2, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_multiply(&matrix_A, NULL, &res_matrix);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_matrix_multiply_null_result)
{
    matrix_t matrix_A = {2, 2, NULL};
    matrix_t matrix_B = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_multiply(&matrix_A, &matrix_B, NULL);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_matrix_multiply_invalid_dimensions)
{
    matrix_t matrix_A = {2, 3, NULL};
    matrix_t matrix_B = {2, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    matrix_alloc(&matrix_A.matrix_data, 2, 3);
    matrix_alloc(&matrix_B.matrix_data, 2, 2);
    matrix_alloc(&res_matrix.matrix_data, 2, 2);
    
    rc = matrix_multiply(&matrix_A, &matrix_B, &res_matrix);
    ck_assert_int_eq(rc, ERR_MATRIX_DIMENSIONS);
    
    free_matrix(&matrix_A.matrix_data, matrix_A.rows);
    free_matrix(&matrix_B.matrix_data, matrix_B.rows);
    free_matrix(&res_matrix.matrix_data, res_matrix.rows);
}
END_TEST

START_TEST(test_matrix_multiply_normal_case)
{
    matrix_t matrix_A = {2, 3, NULL};
    matrix_t matrix_B = {3, 2, NULL};
    matrix_t res_matrix = {2, 2, NULL};
    error_t rc;
    
    matrix_alloc(&matrix_A.matrix_data, 2, 3);
    matrix_alloc(&matrix_B.matrix_data, 3, 2);
    matrix_alloc(&res_matrix.matrix_data, 2, 2);
    
    matrix_A.matrix_data[0][0] = 1.0; matrix_A.matrix_data[0][1] = 2.0; matrix_A.matrix_data[0][2] = 3.0;
    matrix_A.matrix_data[1][0] = 4.0; matrix_A.matrix_data[1][1] = 5.0; matrix_A.matrix_data[1][2] = 6.0;
    
    matrix_B.matrix_data[0][0] = 7.0; matrix_B.matrix_data[0][1] = 8.0;
    matrix_B.matrix_data[1][0] = 9.0; matrix_B.matrix_data[1][1] = 10.0;
    matrix_B.matrix_data[2][0] = 11.0; matrix_B.matrix_data[2][1] = 12.0;
    
    rc = matrix_multiply(&matrix_A, &matrix_B, &res_matrix);
    ck_assert_int_eq(rc, OK);
    ck_assert_double_eq(res_matrix.matrix_data[0][0], 58.0);
    ck_assert_double_eq(res_matrix.matrix_data[0][1], 64.0);
    ck_assert_double_eq(res_matrix.matrix_data[1][0], 139.0);
    ck_assert_double_eq(res_matrix.matrix_data[1][1], 154.0);
    
    free_matrix(&matrix_A.matrix_data, matrix_A.rows);
    free_matrix(&matrix_B.matrix_data, matrix_B.rows);
    free_matrix(&res_matrix.matrix_data, res_matrix.rows);
}
END_TEST

Suite *matrix_operations_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("matrix_operations");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_matrix_addition_normal_case);
    tcase_add_test(tc_pos, test_matrix_multiply_normal_case);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_matrix_addition_null_first);
    tcase_add_test(tc_neg, test_matrix_addition_null_second);
    tcase_add_test(tc_neg, test_matrix_addition_null_result);
    tcase_add_test(tc_neg, test_matrix_addition_invalid_dimensions);
    tcase_add_test(tc_neg, test_matrix_multiply_null_first);
    tcase_add_test(tc_neg, test_matrix_multiply_null_second);
    tcase_add_test(tc_neg, test_matrix_multiply_null_result);
    tcase_add_test(tc_neg, test_matrix_multiply_invalid_dimensions);
    suite_add_tcase(s, tc_neg);

    return s;
}