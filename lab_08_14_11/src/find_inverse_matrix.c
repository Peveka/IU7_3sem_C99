#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "find_inverse_matrix.h"
#include "matrix_memory_handle.h"
#include "matrix.h"

#define EPS 1e-10

static error_t swap_rows(double *row1, double *row2, int columns)
{
    if (!row1 || !row2 || columns <= 0)
        return ERR_INVALID_DATA;
    
    for (int j = 0; j < columns; j++)
    {
        double temp = row1[j];
        row1[j] = row2[j];
        row2[j] = temp;
    }
    
    return OK;
}

static error_t copy_matrix_data(matrix_t *src, matrix_t *dst)
{
    if (!src || !dst || !src->matrix_data || !dst->matrix_data)
        return ERR_INVALID_DATA;
    
    for (int i = 0; i < src->rows; i++)
        for (int j = 0; j < src->columns; j++)
            dst->matrix_data[i][j] = src->matrix_data[i][j];
    
    return OK;
}

static error_t find_pivot_row(matrix_t *matrix, int col, int *pivot_row)
{
    if (!matrix || !matrix->matrix_data || !pivot_row)
        return ERR_INVALID_DATA;
    
    *pivot_row = col;
    
    for (int i = col + 1; i < matrix->rows; i++)
        if (fabs(matrix->matrix_data[i][col]) > fabs(matrix->matrix_data[*pivot_row][col]))
            *pivot_row = i;
    
    return OK;
}

static error_t normalize_pivot_row(matrix_t *matrix, int pivot)
{
    error_t rc = OK;
    if (!matrix || !matrix->matrix_data)
        return ERR_INVALID_DATA;
    
    double pivot_val = matrix->matrix_data[pivot][pivot];
    
    if (fabs(pivot_val) < EPS)
        rc = ERR_SEARCH_INVERSE_MATRIX;
    
    for (int j = pivot; j < matrix->columns && rc == OK; j++)
        matrix->matrix_data[pivot][j] /= pivot_val;
    
    return rc;
}

static error_t eliminate_column(matrix_t *matrix, int pivot)
{
    if (!matrix || !matrix->matrix_data)
        return ERR_INVALID_DATA;
    
    for (int i = 0; i < matrix->rows; i++)
    {
        if (i != pivot)
        {
            double factor = matrix->matrix_data[i][pivot];
            for (int j = pivot; j < matrix->columns; j++)
                matrix->matrix_data[i][j] -= factor * matrix->matrix_data[pivot][j];
        }
    }
    
    return OK;
}

static error_t perform_elimination(matrix_t *matrix, int pivot)
{
    if (!matrix || !matrix->matrix_data)
        return ERR_INVALID_DATA;
    error_t rc = OK;
    
    if (fabs(matrix->matrix_data[pivot][pivot]) < EPS)
        rc = ERR_SEARCH_INVERSE_MATRIX;
    
    if (rc == OK)
    {
        rc = normalize_pivot_row(matrix, pivot);
        if (rc == OK)
            rc = eliminate_column(matrix, pivot);
    }
    
    return rc;
}

static error_t compute_determinant(matrix_t *temp, double *det)
{
    if (!temp || !det)
        return ERR_INVALID_DATA;
    
    error_t rc = OK;
    *det = 1.0;
    int n = temp->rows;
    
    for (int k = 0; k < n && rc == OK; k++)
    {
        int pivot_row = k;
        rc = find_pivot_row(temp, k, &pivot_row);
        
        if (rc == OK && pivot_row != k)
        {
            rc = swap_rows(temp->matrix_data[k], temp->matrix_data[pivot_row], n);
            if (rc == OK)
                *det = -(*det);
        }
        
        if (rc == OK && fabs(temp->matrix_data[k][k]) < EPS)
            rc = ERR_SEARCH_INVERSE_MATRIX;
        
        if (rc == OK)
        {
            for (int i = k + 1; i < n; i++)
            {
                double factor = temp->matrix_data[i][k] / temp->matrix_data[k][k];
                for (int j = k + 1; j < n; j++)
                    temp->matrix_data[i][j] -= factor * temp->matrix_data[k][j];
            }
            *det *= temp->matrix_data[k][k];
        }
    }
    
    return rc;
}

static error_t check_degenerate_matrix(matrix_t *matrix)
{
    if (!matrix || !matrix->matrix_data || matrix->rows != matrix->columns)
        return ERR_INVALID_DATA;
    
    error_t rc = OK;
    matrix_t temp = { 0, 0, NULL};
    double det = 1.0;
    
    rc = matrix_alloc(&temp.matrix_data, matrix->rows, matrix->columns);
    
    if (rc == OK)
    {
        temp.rows = matrix->rows;
        temp.columns = matrix->columns;
        rc = copy_matrix_data(matrix, &temp);
    }
    
    if (rc == OK)
        rc = compute_determinant(&temp, &det);
    
    if (rc == OK && fabs(det) < EPS)
        rc = ERR_SEARCH_INVERSE_MATRIX;
    
    if (temp.matrix_data)
        free_matrix(&temp.matrix_data, temp.rows);
    
    return rc;
}

static void fill_unit_vector(double **extended, int n, int col_index)
{
    for (int i = 0; i < n; i++)
        extended[i][n] = (i == col_index) ? 1.0 : 0.0;
}

static error_t create_extended_matrix(matrix_t *matrix, int col_index, matrix_t *extended)
{
    if (!matrix || !matrix->matrix_data || !extended || col_index < 0 || col_index >= matrix->rows)
        return ERR_INVALID_DATA;
    
    error_t rc = matrix_alloc(&extended->matrix_data, matrix->rows, matrix->columns + 1);
    
    if (rc == OK)
    {
        extended->rows = matrix->rows;
        extended->columns = matrix->columns + 1;
        rc = copy_matrix_data(matrix, extended);
    }
    
    if (rc == OK)
        fill_unit_vector(extended->matrix_data, matrix->rows, col_index);
    
    return rc;
}

static error_t gaussian_elimination_step(matrix_t *extended, int k)
{
    if (!extended || !extended->matrix_data)
        return ERR_INVALID_DATA;
    
    error_t rc = OK;
    int pivot_row = k;
    
    rc = find_pivot_row(extended, k, &pivot_row);
    
    if (rc == OK && pivot_row != k)
        rc = swap_rows(extended->matrix_data[k], extended->matrix_data[pivot_row], extended->columns);
    
    if (rc == OK)
        rc = perform_elimination(extended, k);
    
    return rc;
}

static error_t gaussian_forward_elimination(matrix_t *extended)
{
    if (!extended || !extended->matrix_data)
        return ERR_INVALID_DATA;
    
    error_t rc = OK;
    int n = extended->rows;
    
    for (int k = 0; k < n && rc == OK; k++)
        rc = gaussian_elimination_step(extended, k);
    
    return rc;
}

static error_t extract_solution(matrix_t *extended, double *result_column)
{
    if (!extended || !extended->matrix_data || !result_column)
        return ERR_INVALID_DATA;
    
    for (int i = 0; i < extended->rows; i++)
        result_column[i] = extended->matrix_data[i][extended->columns - 1];
    
    return OK;
}

static error_t solve_for_column(matrix_t *matrix, int col_index, double *result_column)
{
    if (!matrix || !matrix->matrix_data || !result_column)
        return ERR_INVALID_DATA;

    error_t rc = OK;
    matrix_t extended = { 0, 0, NULL };

    rc = create_extended_matrix(matrix, col_index, &extended);

    if (rc == OK)
        rc = gaussian_forward_elimination(&extended);

    if (rc == OK)
        rc = extract_solution(&extended, result_column);

    if (extended.matrix_data)
        free_matrix(&extended.matrix_data, extended.rows);

    return rc;
}

static error_t validate_input(matrix_t *matrix, matrix_t *inverse_matrix)
{
    if (!matrix || !inverse_matrix)
        return ERR_INVALID_DATA;
    if (!matrix->matrix_data)
        return ERR_INVALID_DATA;
    if (matrix->rows != matrix->columns || matrix->rows <= 0)
        return ERR_INVALID_DATA;
    return OK;
}

static error_t init_inverse_matrix(matrix_t *src, matrix_t *dst)
{
    error_t rc = matrix_alloc(&dst->matrix_data, src->rows, src->columns);
    if (rc == OK)
    {
        dst->rows = src->rows;
        dst->columns = src->columns;
    }
    return rc;
}

static error_t fill_inverse_matrix_by_columns(matrix_t *src_matrix, matrix_t *inverse)
{
    const int n = src_matrix->rows;
    double *solution = NULL;
    error_t rc = vector_alloc(&solution, n);
    
    if (rc != OK)
        return rc;

    for (int j = 0; j < n && rc == OK; j++)
    {
        rc = solve_for_column(src_matrix, j, solution);
        if (rc == OK)
        {
            for (int i = 0; i < n; i++)
                inverse->matrix_data[i][j] = solution[i];
        }
    }

    vector_free(solution);
    return rc;
}

error_t find_inverse_matrix_gauss(matrix_t *matrix, matrix_t *inverse_matrix)
{
    error_t rc = validate_input(matrix, inverse_matrix);
    if (rc != OK)
        return rc;
    
    if (rc == OK)
        rc = check_degenerate_matrix(matrix);
    if (rc == OK)
        rc = init_inverse_matrix(matrix, inverse_matrix);
    if (rc == OK)
        rc = fill_inverse_matrix_by_columns(matrix, inverse_matrix);

    if (rc != OK)
    {
        free_matrix(&inverse_matrix->matrix_data, inverse_matrix->rows);
        inverse_matrix->rows = 0;
        inverse_matrix->columns = 0;
    }

    return rc;
}