#include <stdio.h>
#include "errors.h"
#include "matrix.h"

error_t matrix_addition(matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res_matrix)
{
    error_t rc = OK;
    
    if (first_matrix == NULL || second_matrix == NULL || res_matrix == NULL)
        return ERR_INVALID_DATA;
    
    if (first_matrix->rows <= 0 || first_matrix->columns <= 0 || first_matrix->matrix_data == NULL)
        return ERR_INVALID_DATA;
    if (second_matrix->rows <= 0 || second_matrix->columns <= 0 || second_matrix->matrix_data == NULL)
        return ERR_INVALID_DATA;
    if (res_matrix->matrix_data == NULL)
        return ERR_INVALID_DATA;

    if (first_matrix->rows != second_matrix->rows || first_matrix->columns != second_matrix->columns)
        rc = ERR_MATRIX_DIMENSIONS;

    if (rc == OK)
    {
        res_matrix->rows = first_matrix->rows;
        res_matrix->columns = first_matrix->columns;
    }

    for (int i = 0; i < res_matrix->rows && rc == OK; ++i)
        for (int j = 0; j < res_matrix->columns && rc == OK; ++j)
        {
            double result = (first_matrix->matrix_data)[i][j] + (second_matrix->matrix_data)[i][j];
            (res_matrix->matrix_data)[i][j] = result;
        }

    return rc;
}

error_t matrix_multiply(matrix_t *first_matrix, matrix_t *second_matrix, matrix_t *res_matrix)
{
    error_t rc = OK;
    
    if (first_matrix == NULL || second_matrix == NULL || res_matrix == NULL)
        return ERR_INVALID_DATA;
    
    if (first_matrix->rows <= 0 || first_matrix->columns <= 0 || first_matrix->matrix_data == NULL)
        return ERR_INVALID_DATA;
    if (second_matrix->rows <= 0 || second_matrix->columns <= 0 || second_matrix->matrix_data == NULL)
        return ERR_INVALID_DATA;
    if (res_matrix->matrix_data == NULL)
        return ERR_INVALID_DATA;

    if (first_matrix->columns != second_matrix->rows)
        return ERR_MATRIX_DIMENSIONS;
    
    if (rc == OK)
    {
        res_matrix->rows = first_matrix->rows;
        res_matrix->columns = second_matrix->columns;
    }

    for (int i = 0; i < res_matrix->rows && rc == OK; ++i)
        for (int j = 0; j < res_matrix->columns && rc == OK; ++j)
        {
            double sum = 0.0;
            for (int k = 0; k < first_matrix->columns && rc == OK; ++k)
                sum += first_matrix->matrix_data[i][k] * second_matrix->matrix_data[k][j];
            res_matrix->matrix_data[i][j] = sum;
        }

    return rc;
}