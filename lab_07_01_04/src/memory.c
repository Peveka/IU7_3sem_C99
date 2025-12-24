#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

error_t allocate_memory_with_check(size_t size, void **arr_ptr)
{
    error_t rc = OK;
    if (size <= 0 || arr_ptr == NULL)
        return ERROR_INVALID_DATA;

    
    *arr_ptr = malloc(size);
    if (*arr_ptr == NULL)
        rc = ERROR_MEMORY_ALLOCATION;
    return rc;
}

void free_memory(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
}