#include <check.h>
#include <stdlib.h>
#include "data.h"
#include "polynom_operations.h"
#include "mem_allocation.h"
#include "list_operations.h"

START_TEST(test_evaluate_polynome_val)
{
    polynom_t *poly = NULL;
    int coeffs[] = {4, 2, 0, 6}; // 4x^3 + 2x^2 + 0x + 6
    int result;
    error_t rc;
    
    rc = create_polynom(&poly, coeffs, 4);
    ck_assert_int_eq(rc, OK);
    
    // Тестируем P(0) = 6
    rc = evaluate_polynome(&result, poly, 0);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(result, 6);
    
    // Тестируем P(1) = 4 + 2 + 0 + 6 = 12
    rc = evaluate_polynome(&result, poly, 1);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(result, 12);
    
    // Тестируем P(2) = 4*8 + 2*4 + 0 + 6 = 32 + 8 + 6 = 46
    rc = evaluate_polynome(&result, poly, 2);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(result, 46);
    
    // Тестируем P(7) = 4*343 + 2*49 + 0 + 6 = 1372 + 98 + 6 = 1476
    rc = evaluate_polynome(&result, poly, 7);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(result, 1476);
    
    polynome_free(&poly);
}
END_TEST

START_TEST(test_ddx_polynome)
{
    polynom_t *poly = NULL;
    int coeffs[] = {4, 2, 0, 6}; // 4x^3 + 2x^2 + 0x + 6
    int *ddx_coeffs = NULL;
    int size = 4;
    error_t rc;
    
    rc = create_polynom(&poly, coeffs, 4);
    ck_assert_int_eq(rc, OK);
    
    rc = ddx_polynome(poly, &ddx_coeffs, &size);
    ck_assert_int_eq(rc, OK);
    
    // 12x^2 + 4x + 0
    ck_assert_int_eq(size, 3);
    ck_assert_ptr_nonnull(ddx_coeffs);
    ck_assert_int_eq(ddx_coeffs[0], 12);
    ck_assert_int_eq(ddx_coeffs[1], 4);
    ck_assert_int_eq(ddx_coeffs[2], 0);
    
    free_coef_data(&ddx_coeffs);
    polynome_free(&poly);
}
END_TEST


START_TEST(test_polynome_add_sum)
{
    polynom_t *poly1 = NULL, *poly2 = NULL;
    int coeffs1[] = {4, 2, 0, 6}; // 4x^3 + 2x^2 + 0x + 6
    int coeffs2[] = {12, 4, 0};   // 12x^2 + 4x + 0
    int *result_coeffs = NULL;
    int result_size = 0;
    error_t rc;
    
    rc = create_polynom(&poly1, coeffs1, 4);
    ck_assert_int_eq(rc, OK);
    
    rc = create_polynom(&poly2, coeffs2, 3);
    ck_assert_int_eq(rc, OK);
    
    rc = polynome_add(poly1, poly2, &result_coeffs, &result_size);
    ck_assert_int_eq(rc, OK);
    
    // 4x^3 + 14x^2 + 4x + 6
    ck_assert_int_eq(result_size, 4);
    ck_assert_ptr_nonnull(result_coeffs);
    ck_assert_int_eq(result_coeffs[0], 4);
    ck_assert_int_eq(result_coeffs[1], 14);
    ck_assert_int_eq(result_coeffs[2], 4);
    ck_assert_int_eq(result_coeffs[3], 6);
    
    free_coef_data(&result_coeffs);
    polynome_free(&poly1);
    polynome_free(&poly2);
}
END_TEST

START_TEST(test_divide_polynome_dvd)
{
    polynom_t *poly = NULL;
    int coeffs[] = {4, 2, 0, 6}; // 4x^3 + 2x^2 + 0x + 6
    int *even_coeffs = NULL, *odd_coeffs = NULL;
    int even_size = 0, odd_size = 0;
    error_t rc;
    
    rc = create_polynom(&poly, coeffs, 4);
    ck_assert_int_eq(rc, OK);
    
    rc = divide_polynome(poly, &even_coeffs, &even_size, &odd_coeffs, &odd_size);
    ck_assert_int_eq(rc, OK);
    
    // Четные степени: 2x^2 + 6
    ck_assert_int_eq(even_size, 2);
    ck_assert_ptr_nonnull(even_coeffs);
    ck_assert_int_eq(even_coeffs[0], 2);
    ck_assert_int_eq(even_coeffs[1], 6);
    
    // Нечетные степени: 4x^3 + 0x
    ck_assert_int_eq(odd_size, 2);
    ck_assert_ptr_nonnull(odd_coeffs);
    ck_assert_int_eq(odd_coeffs[0], 4);
    ck_assert_int_eq(odd_coeffs[1], 0);
    
    free_coef_data(&even_coeffs);
    free_coef_data(&odd_coeffs);
    polynome_free(&poly);
}
END_TEST

START_TEST(test_single_constant_polynome)
{
    polynom_t *poly = NULL;
    int coeffs[] = {5};
    int result;
    error_t rc;
    
    rc = create_polynom(&poly, coeffs, 1);
    ck_assert_int_eq(rc, OK);
    
    rc = evaluate_polynome(&result, poly, 10);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(result, 5);
    
    rc = evaluate_polynome(&result, poly, 100);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(result, 5);
    
    polynome_free(&poly);
}
END_TEST

START_TEST(test_ddx_constant)
{
    polynom_t *poly = NULL;
    int coeffs[] = {5};
    int *ddx_coeffs = NULL;
    int size = 1;
    error_t rc;
    
    rc = create_polynom(&poly, coeffs, 1);
    ck_assert_int_eq(rc, OK);
    
    rc = ddx_polynome(poly, &ddx_coeffs, &size);
    ck_assert_int_eq(rc, OK);
    
    ck_assert_int_eq(size, 0);
    
    free_coef_data(&ddx_coeffs);
    polynome_free(&poly);
}
END_TEST

Suite *polynom_operations_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("PolynomOperations");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_evaluate_polynome_val);
    tcase_add_test(tc_core, test_ddx_polynome);
    tcase_add_test(tc_core, test_polynome_add_sum);
    tcase_add_test(tc_core, test_divide_polynome_dvd);
    tcase_add_test(tc_core, test_single_constant_polynome);
    tcase_add_test(tc_core, test_ddx_constant);

    suite_add_tcase(s, tc_core);

    return s;
}