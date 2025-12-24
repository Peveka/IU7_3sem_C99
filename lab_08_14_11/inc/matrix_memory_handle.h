#ifndef MATRIX_MEMORY_H__
#define MATRIX_MEMORY_H__
#include "errors.h"

error_t vector_alloc(double **vector, int n);
void vector_free(double *vector);
void free_matrix(double ***matrix, int n);
error_t matrix_alloc(double ***matrix, int n, int m);

#endif