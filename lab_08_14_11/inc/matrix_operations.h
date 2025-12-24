#ifndef MATRIX_OPERATIONS_H__
#define MATRIX_OPERATIONS_H__
#include "errors.h"
#include "matrix.h"

error_t matrix_addition(matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res_matrix);
error_t matrix_multiply(matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res_matrix);

#endif