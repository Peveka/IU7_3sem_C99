#include "matrix_io.h"
#include <stdio.h>
#include "errors.h"
#include "matrix_memory_handle.h"

static error_t check_extra_data(FILE *file)
{
    error_t rc = OK;
    double extra;
    if (fscanf(file, "%lf", &extra) == 1)
        rc = ERR_EXTRA_DATA_IN_FILE;
    return rc;
}

static error_t check_empty_file(FILE *file)
{
    error_t rc = OK;
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) 
        rc = ERR_FILE_IS_EMPTY;
    fseek(file, 0, SEEK_SET);

    return rc;
}

error_t matrix_input(const char *filename, matrix_t *matrix)
{
    if (!filename || !matrix || filename[0] == '\0')
        return ERR_INVALID_DATA;

    matrix->rows = 0;
    matrix->columns = 0;
    matrix->matrix_data = NULL;

    error_t rc = OK;
    FILE *file = fopen(filename, "r");
    int file_open_flag = 0;
    if (!file)
        rc = ERR_INVALID_FILE;
    else
    {
        file_open_flag = 1;
        rc = check_empty_file(file);
    }
        
    if (rc == OK && fscanf(file, "%d %d", &(matrix->rows), &(matrix->columns)) != 2)
        rc = ERR_INVALID_DATA;

    if (rc == OK && (matrix->rows <= 0 || matrix->columns <= 0))
        rc = ERR_INVALID_DATA;
    else if (rc == OK)
        rc = matrix_alloc(&(matrix->matrix_data), matrix->rows, matrix->columns);

    for (int i = 0; i < matrix->rows && rc == OK; ++i)
        for (int k = 0; k < matrix->columns && rc == OK; ++k)
        {
            int read_status = fscanf(file, "%lf", &(matrix->matrix_data)[i][k]);
            if (read_status == EOF)
                rc = ERR_NOT_ENOUGH_DATA;
            else if (read_status == 0)
                rc = ERR_INVALID_DATA;
        }
            
    
    if (rc == OK)
        rc = check_extra_data(file);
    
    if (rc != OK)
    {
        free_matrix(&matrix->matrix_data, matrix->rows);
        matrix->rows = 0;
        matrix->columns = 0;
    }

    if (file_open_flag == 1)
        fclose(file);

    return rc;
}

error_t matrix_output(const char *filename, matrix_t *matrix)
{
    if (!filename || !matrix || filename[0] == '\0')
        return ERR_INVALID_DATA;
    error_t rc = OK;
    FILE *file = fopen(filename, "w");
    int file_open_flag = 0;
    if (!file)
        rc = ERR_INVALID_FILE;
    else
        file_open_flag = 1;

    if (rc == OK)
        fprintf(file, "%d %d\n", matrix->rows, matrix->columns);
    for (int i = 0; i < matrix->rows && rc == OK; ++i)
    {
        for (int k = 0; k < matrix->columns && rc == OK; ++k)
            fprintf(file, "%.6f ", (matrix->matrix_data)[i][k]);
        fprintf(file, "\n");
    }

    if (file_open_flag == 1)
    {
        fseek(file, 0, SEEK_END);
        fclose(file);
    }
    return rc;
}