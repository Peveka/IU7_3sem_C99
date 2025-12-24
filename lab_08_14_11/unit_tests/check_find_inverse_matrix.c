#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "find_inverse_matrix.h"
#include "matrix_memory_handle.h"
#include "check_find_inverse_matrix.h"

#define EPS 1e-6

START_TEST(test_find_inverse_matrix_null_matrix)
{
    matrix_t inverse_matrix = {2, 2, NULL};
    error_t rc;
    
    rc = find_inverse_matrix_gauss(NULL, &inverse_matrix);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
}
END_TEST

START_TEST(test_find_inverse_matrix_null_result)
{
    matrix_t matrix = {2, 2, NULL};
    error_t rc;
    
    rc = matrix_alloc(&matrix.matrix_data, 2, 2);
    ck_assert_int_eq(rc, OK);
    
    rc = find_inverse_matrix_gauss(&matrix, NULL);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
    
    free_matrix(&matrix.matrix_data, matrix.rows);
}
END_TEST

START_TEST(test_find_inverse_matrix_non_square)
{
    matrix_t matrix = {2, 3, NULL};
    matrix_t inverse_matrix = {2, 2, NULL};
    error_t rc;
    
    matrix_alloc(&matrix.matrix_data, 2, 3);
    rc = find_inverse_matrix_gauss(&matrix, &inverse_matrix);
    ck_assert_int_eq(rc, ERR_INVALID_DATA);
    
    free_matrix(&matrix.matrix_data, matrix.rows);
}
END_TEST

START_TEST(test_find_inverse_matrix_degenerate)
{
    matrix_t matrix = {2, 2, NULL};
    matrix_t inverse_matrix = {2, 2, NULL};
    error_t rc;
    
    matrix_alloc(&matrix.matrix_data, 2, 2);
    matrix.matrix_data[0][0] = 1.0; matrix.matrix_data[0][1] = 2.0;
    matrix.matrix_data[1][0] = 2.0; matrix.matrix_data[1][1] = 4.0;
    
    rc = find_inverse_matrix_gauss(&matrix, &inverse_matrix);
    ck_assert_int_eq(rc, ERR_SEARCH_INVERSE_MATRIX);
    
    free_matrix(&matrix.matrix_data, matrix.rows);
}
END_TEST

START_TEST(test_find_inverse_matrix_3x3)
{
    matrix_t matrix = {3, 3, NULL};
    matrix_t inverse_matrix = {3, 3, NULL};
    error_t rc;
    
    matrix_alloc(&matrix.matrix_data, 3, 3);
    
    matrix.matrix_data[0][0] = 2.0; matrix.matrix_data[0][1] = 1.0; matrix.matrix_data[0][2] = 1.0;
    matrix.matrix_data[1][0] = 1.0; matrix.matrix_data[1][1] = 2.0; matrix.matrix_data[1][2] = 1.0;
    matrix.matrix_data[2][0] = 1.0; matrix.matrix_data[2][1] = 1.0; matrix.matrix_data[2][2] = 2.0;
    
    rc = find_inverse_matrix_gauss(&matrix, &inverse_matrix);
    ck_assert_int_eq(rc, OK);
    
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[0][0], 0.75, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[0][1], -0.25, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[0][2], -0.25, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[1][0], -0.25, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[1][1], 0.75, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[1][2], -0.25, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[2][0], -0.25, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[2][1], -0.25, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[2][2], 0.75, EPS);
    
    free_matrix(&matrix.matrix_data, matrix.rows);
    free_matrix(&inverse_matrix.matrix_data, inverse_matrix.rows);
}
END_TEST

START_TEST(test_find_inverse_matrix_identity)
{
    matrix_t matrix = {3, 3, NULL};
    matrix_t inverse_matrix = {3, 3, NULL};
    error_t rc;
    
    matrix_alloc(&matrix.matrix_data, 3, 3);
    
    matrix.matrix_data[0][0] = 1.0; matrix.matrix_data[0][1] = 0.0; matrix.matrix_data[0][2] = 0.0;
    matrix.matrix_data[1][0] = 0.0; matrix.matrix_data[1][1] = 1.0; matrix.matrix_data[1][2] = 0.0;
    matrix.matrix_data[2][0] = 0.0; matrix.matrix_data[2][1] = 0.0; matrix.matrix_data[2][2] = 1.0;
    
    rc = find_inverse_matrix_gauss(&matrix, &inverse_matrix);
    ck_assert_int_eq(rc, OK);
    
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[0][0], 1.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[0][1], 0.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[0][2], 0.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[1][0], 0.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[1][1], 1.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[1][2], 0.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[2][0], 0.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[2][1], 0.0, EPS);
    ck_assert_double_eq_tol(inverse_matrix.matrix_data[2][2], 1.0, EPS);
    
    free_matrix(&matrix.matrix_data, matrix.rows);
    free_matrix(&inverse_matrix.matrix_data, inverse_matrix.rows);
}
END_TEST

Suite *find_inverse_matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("find_inverse_matrix");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_find_inverse_matrix_3x3);
    tcase_add_test(tc_pos, test_find_inverse_matrix_identity);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_find_inverse_matrix_null_matrix);
    tcase_add_test(tc_neg, test_find_inverse_matrix_null_result);
    tcase_add_test(tc_neg, test_find_inverse_matrix_non_square);
    tcase_add_test(tc_neg, test_find_inverse_matrix_degenerate);
    suite_add_tcase(s, tc_neg);

    return s;
}