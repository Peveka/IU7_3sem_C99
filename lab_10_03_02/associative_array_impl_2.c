#include <stdlib.h>
#include <string.h>
#include "associative_array.h"
#include "mem_allocation_darray.h"
#include "darray.h"
#include "darray_operations.h"

#define INITIAL_CAPACITY 10

assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = NULL;
    
    arr = array_alloc();
    if (arr != NULL)
    {
        arr->items = items_alloc(INITIAL_CAPACITY);
        if (arr->items != NULL)
        {
            arr->size = 0;
            arr->capacity = INITIAL_CAPACITY;
        }
        else
        {
            array_free(arr);
            arr = NULL;
        }
    }
    
    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;

    assoc_array_clear(*arr);
    items_free((*arr)->items);
    array_free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || num == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;
    
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    int index = find_key_index(arr, key);
    if (index != -1)
        *num = &(arr->items[index].value);
    else
        rc = ASSOC_ARRAY_NOT_FOUND;

    return rc;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{    
    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    int index = find_key_index(arr, key);
    if (index != -1)
        rc = ASSOC_ARRAY_KEY_EXISTS;
    else
    {
        rc = arr_resize(arr);
        if (rc == ASSOC_ARRAY_OK)
        {
            char *key_copy = key_alloc(strlen(key) + 1);
            if (key_copy != NULL)
            {
                strcpy(key_copy, key);
                arr->items[arr->size].key = key_copy;
                arr->items[arr->size].value = num;
                arr->size++;
            }
            else
                rc = ASSOC_ARRAY_MEM;
        }
    }
    
    return rc;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    int index = find_key_index(arr, key);
    if (index != -1)
        rc = delete_item(arr, (size_t)index);
    else
        rc = ASSOC_ARRAY_NOT_FOUND;

    return rc;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    for (size_t i = 0; i < arr->size; i++)
        key_free(arr->items[i].key);

    arr->size = 0;
    return rc;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    for (size_t i = 0; i < arr->size; i++)
        action(arr->items[i].key, &(arr->items[i].value), param);
    
    return rc;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr->size > 0)
    {
        size_t min_index = 0;
        for (size_t i = 1; i < arr->size; i++)
            if (strcmp(arr->items[i].key, arr->items[min_index].key) < 0)
                min_index = i;
        
        *num = &(arr->items[min_index].value);
    }
    else
        rc = ASSOC_ARRAY_NOT_FOUND;
    
    return rc;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    if (arr->size > 0)
    {
        size_t max_index = 0;
        for (size_t i = 1; i < arr->size; i++)
            if (strcmp(arr->items[i].key, arr->items[max_index].key) > 0)
                max_index = i;
        
        *num = &(arr->items[max_index].value);
    }
    else
        rc = ASSOC_ARRAY_NOT_FOUND;
    
    return rc;
}