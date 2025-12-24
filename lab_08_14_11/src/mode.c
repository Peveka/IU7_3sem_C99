#include "mode.h"

#include <string.h>

#include "errors.h"
#include "find_inverse_matrix.h"
#include "matrix_io.h"
#include "matrix_memory_handle.h"
#include "matrix_operations.h"

error_t mode_define(int argc, char **argv, action_mode_t *mode)
{
    error_t rc = OK;
    switch (argc)
    {
        case 4: 
            {
                if (strcmp(argv[1], "o") == 0)
                    *mode = INVERSE_MATRIX_MODE;
                else
                {
                    *mode = UNKNOWN_MODE;
                    rc = ERR_UNKNOWN_MODE;
                }
                break;
            }
        case 5: 
            {
                if (strcmp(argv[1], "m") == 0)
                    *mode = MULTIPLY_MODE;
                else if (strcmp(argv[1], "a") == 0)
                    *mode = ADD_MODE;
                else
                {
                    *mode = UNKNOWN_MODE;
                    rc = ERR_UNKNOWN_MODE;
                }
                break;
            }
        default: 
            {
                *mode = UNKNOWN_MODE;
                rc = ERR_UNKNOWN_MODE;
                break;
            }
    }
    return rc;
}

error_t add_mode_handler(const char *filename_first_matr, const char *filename_second_matr,
const char *filename_matr_res, matrix_t *first_matrix, matrix_t *second_matrix,
matrix_t *res_matrix)
{
    error_t rc = matrix_input(filename_first_matr, first_matrix);
    if (rc == OK)
        rc = matrix_input(filename_second_matr, second_matrix);
    if (rc == OK && (first_matrix->rows != second_matrix->rows || first_matrix->columns != second_matrix->columns))
        rc = ERR_MATRIX_DIMENSIONS;
    if (rc == OK)
    {
        rc = matrix_alloc(&(res_matrix->matrix_data), first_matrix->rows, first_matrix->columns);
        if (rc == OK)
        {
            res_matrix->rows = first_matrix->rows;
            res_matrix->columns = first_matrix->columns;
        }
    }
    if (rc == OK)
        rc = matrix_addition(first_matrix, second_matrix, res_matrix);
    if (rc == OK)
        rc = matrix_output(filename_matr_res, res_matrix);

    free_matrix(&(first_matrix->matrix_data), first_matrix->rows);
    free_matrix(&(second_matrix->matrix_data), second_matrix->rows);
    free_matrix(&(res_matrix->matrix_data), res_matrix->rows);

    return rc;
}

error_t multiply_mode_handler(const char *filename_first_matr, const char *filename_second_matr,
const char *filename_matr_res, matrix_t *first_matrix, matrix_t *second_matrix,
matrix_t *res_matrix)
{
    error_t rc = matrix_input(filename_first_matr, first_matrix);
    if (rc == OK)
        rc = matrix_input(filename_second_matr, second_matrix);
    if (rc == OK && first_matrix->columns != second_matrix->rows)
        rc = ERR_MATRIX_DIMENSIONS;
    if (rc == OK)
    {
        rc = matrix_alloc(&(res_matrix->matrix_data), first_matrix->rows, second_matrix->columns);
        if (rc == OK)
        {
            res_matrix->rows = first_matrix->rows;
            res_matrix->columns = second_matrix->columns;
        }
    }
    if (rc == OK)
        rc = matrix_multiply(first_matrix, second_matrix, res_matrix);
    if (rc == OK)
        rc = matrix_output(filename_matr_res, res_matrix);

    free_matrix(&(first_matrix->matrix_data), first_matrix->rows);
    free_matrix(&(second_matrix->matrix_data), second_matrix->rows);
    free_matrix(&(res_matrix->matrix_data), res_matrix->rows);

    return rc;
}

error_t inverse_mode_handler(const char *filename_input, const char *filename_output, matrix_t *matrix,
matrix_t *inverse_matrix)
{
    error_t rc = matrix_input(filename_input, matrix);

    if (rc == OK && matrix->rows != matrix->columns)
        rc = ERR_MATRIX_DIMENSIONS;

    if (rc == OK)
        rc = find_inverse_matrix_gauss(matrix, inverse_matrix);

    if (rc == OK)
        rc = matrix_output(filename_output, inverse_matrix);

    free_matrix(&(matrix->matrix_data), matrix->rows);
    free_matrix(&(inverse_matrix->matrix_data), inverse_matrix->rows);

    return rc;
}