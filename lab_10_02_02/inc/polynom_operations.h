#ifndef POLYNOM_OPERATIONS_H__
#define POLYNOM_OPERATIONS_H__

#include "data.h"
#include "errors.h"

error_t create_polynom(polynom_t **polynome, int *coef_arr, int coef_arr_len);
error_t evaluate_polynome(int *result, polynom_t *polynome, int a);
error_t polynome_add(polynom_t *first_polynome, polynom_t *second_polynome, int **result_coeffs, int *result_size);
error_t ddx_polynome(polynom_t *polynome, int **ddx_coefs, int *polynome_size);
error_t divide_polynome(polynom_t *polynome, int **even_coeffs, int *even_size, int **odd_coeffs, int *odd_size);

#endif