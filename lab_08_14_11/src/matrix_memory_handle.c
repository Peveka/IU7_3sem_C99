#include <stdlib.h>

#include "errors.h"

void free_matrix(double ***matrix, int n)
{
    if (!matrix || !*matrix)
        return;

    for (int i = 0; i < n; ++i)
        free((*matrix)[i]);
    free(*matrix);
    *matrix = NULL;
}

error_t matrix_alloc(double ***matrix, int n, int m)
{
    if (!matrix || n <= 0 || m <= 0)
        return ERR_INVALID_DATA;

    error_t rc = OK;
    *matrix = calloc(n, sizeof(double *));
    if (!(*matrix))
        rc = ERR_MEMORY_ALLOC;
    for (int i = 0; i < n && rc == OK; ++i)
    {
        (*matrix)[i] = malloc(m * sizeof(double));
        if (!(*matrix)[i])
        {
            free_matrix(matrix, n);
            rc = ERR_MEMORY_ALLOC;
        }
    }
    return rc;
}

error_t vector_alloc(double **vector, int n)
{
    error_t rc = OK;
    if (!vector || n <= 0)
        return ERR_INVALID_DATA;

    *vector = malloc(n * sizeof(double));
    if (!*vector)
        rc = ERR_MEMORY_ALLOC;

    return rc;
}

void vector_free(double *vector)
{
    if (vector)
        free(vector);
}