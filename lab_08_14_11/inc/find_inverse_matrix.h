#ifndef FIND_INVERSE_MATRIX_H__
#define FIND_INVERSE_MATRIX_H__

#include "errors.h"
#include "matrix.h"

error_t find_inverse_matrix_gauss(matrix_t *matrix, matrix_t *inverse_matrix);

#endif