#ifndef MATRIX_IO_H__
#define MATRIX_IO_H__
#include "errors.h"
#include "matrix.h"

error_t matrix_input(const char *filename, matrix_t *matrix);
error_t matrix_output(const char *filename, matrix_t *matrix);

#endif