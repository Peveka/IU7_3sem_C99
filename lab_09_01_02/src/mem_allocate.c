#include <stdlib.h>
#include "errors.h"
#include "data.h"

error_t struct_allocate(item_t **items_struct, int elem_count)
{
    error_t rc = OK;
    if (elem_count <= 0 || items_struct == NULL)
        return ERROR_INVALID_DATA;
    *items_struct = malloc(sizeof(item_t) * elem_count);
    if (*items_struct == NULL)
        rc = ERROR_STRUCT_ALLOCATION;
    else 
    {
        for (int i = 0; i < elem_count; i++) 
        {
            (*items_struct)[i].name = NULL;
        }
    }

    return rc;
}

error_t name_allocate(char **name, int size)
{
    error_t rc = OK;
    if (!name || size <= 0)
        return ERROR_INVALID_DATA;
    *name = malloc(sizeof(char) * (size + 1));
    if (!(*name))
        rc = ERROR_NAME_ALLOCATION;
    return rc;
}

void name_free(char **name)
{
    if (name == NULL)
        return;
    free(*name);
    *name = NULL;
}

void struct_free(item_t **items_struct, int struct_len)
{
    if (items_struct == NULL)
        return;
    for (int i = 0; i < struct_len; ++i)
    {
        if (((*items_struct) + i)->name != NULL)
            free(((*items_struct) + i)->name); 
    }
    free(*items_struct); 
    *items_struct = NULL;
}