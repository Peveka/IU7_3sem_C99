#ifndef MODE_H__
#define MODE_H__
#include "errors.h"
#include "matrix.h"

typedef enum
{
    UNKNOWN_MODE = 0,
    ADD_MODE,
    MULTIPLY_MODE,
    INVERSE_MATRIX_MODE,
} action_mode_t;

error_t mode_define(int argc, char **argv, action_mode_t *mode);

error_t add_mode_handler(const char *filename_first_matr, const char *filename_second_matr, const char *filename_matr_res,
matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res_matrix);

error_t multiply_mode_handler(const char *filename_first_matr, const char *filename_second_matr, const char *filename_matr_res,
matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res_matrix);

error_t inverse_mode_handler(const char *filename_input, const char *filename_output, matrix_t *matrix,
matrix_t *inverse_matrix);
#endif