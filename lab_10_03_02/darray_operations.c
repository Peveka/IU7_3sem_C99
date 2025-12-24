#include <stdlib.h>
#include <string.h>
#include "darray_operations.h"
#include "mem_allocation_darray.h"

#define GROWTH_FACTOR 2

int find_key_index(const assoc_array_t arr, const char *key)
{
    int result = -1;
    int found = 0;
    
    if (arr != NULL && key != NULL)
    {
        for (size_t i = 0; !found && i < arr->size; i++)
        {
            if (strcmp(arr->items[i].key, key) == 0)
            {
                result = (int)i;
                found = 1;
            }
        }
    }
    
    return result;
}

assoc_array_error_t arr_resize(assoc_array_t arr)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    
    if (arr->size >= arr->capacity)
    {
        size_t new_capacity = arr->capacity * GROWTH_FACTOR;
        key_value_t *new_items = items_realloc(arr->items, new_capacity);
        if (new_items != NULL)
        {
            arr->items = new_items;
            arr->capacity = new_capacity;
        }
        else
        {
            rc = ASSOC_ARRAY_MEM;
        }
    }
    
    return rc;
}

assoc_array_error_t delete_item(assoc_array_t arr, size_t index)
{
    assoc_array_error_t rc = ASSOC_ARRAY_INVALID_PARAM;
    
    if (arr != NULL && index < arr->size)
    {
        key_free(arr->items[index].key);
        
        for (size_t i = index; i < arr->size - 1; i++)
        {
            arr->items[i] = arr->items[i + 1];
        }
        
        arr->size--;
        rc = ASSOC_ARRAY_OK;
    }
    
    return rc;
}