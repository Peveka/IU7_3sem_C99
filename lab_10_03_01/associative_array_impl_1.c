#include <stdlib.h>
#include <string.h>

#include "mem_allocation.h"
#include "list.h"
#include "associative_array.h"

assoc_array_t assoc_array_create(void)
{
    assoc_array_t array = array_alloc();
    if (array != NULL)
        array->head = NULL;
    return array;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;

    list_free(*arr);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || num == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;
        
    node_t *finded_item = list_search(arr, key);
    if (finded_item != NULL)
        *num = &(finded_item->value);

    return ((finded_item != NULL) ? ASSOC_ARRAY_OK : ASSOC_ARRAY_NOT_FOUND);
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    node_t *searched_node = list_search(arr, key);
    if (searched_node != NULL)
        rc = ASSOC_ARRAY_KEY_EXISTS;
    else
    {
        node_t *node_to_insert = node_alloc();
        rc = create_node(node_to_insert, key, num);
        if (rc == ASSOC_ARRAY_OK && arr->head == NULL)
            arr->head = node_to_insert;
        else if (rc == ASSOC_ARRAY_OK)
        {   
            node_t *cur_node = arr->head;
            for (; cur_node->next != NULL; cur_node = cur_node->next);
            cur_node->next = node_to_insert;
        }
        else if (rc == ASSOC_ARRAY_MEM)
            list_free(arr);
    }

    return rc;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || key[0] == '\0')
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *searched_node = list_search(arr, key);
    assoc_array_error_t rc = ASSOC_ARRAY_OK;

    if (searched_node != NULL)
        rc = delete_node(arr, searched_node);
    else
        rc = ASSOC_ARRAY_NOT_FOUND;

    return rc;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    for (node_t *current_node = arr->head; current_node != NULL;)
    {
        node_t *node_to_remove = current_node;
        current_node = current_node->next;
        node_free(node_to_remove);
    }

    arr->head = NULL;
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL || param == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    for (node_t *current_node = arr->head; current_node != NULL; current_node = current_node->next)
        action(current_node->key, &(current_node->value), param);
    
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    node_t *min_node = NULL;
    for (node_t *current_node = arr->head; current_node != NULL; current_node = current_node->next)
        if (min_node == NULL || strcmp(current_node->key, min_node->key) < 0)
            min_node = current_node;
    
    if (min_node == NULL)
        rc = ASSOC_ARRAY_NOT_FOUND;
    else
        *num = &(min_node->value);

    return rc;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    assoc_array_error_t rc = ASSOC_ARRAY_OK;
    node_t *max_node = NULL;
    for (node_t *current_node = arr->head; current_node != NULL; current_node = current_node->next)
        if (max_node == NULL || strcmp(current_node->key, max_node->key) > 0)
            max_node = current_node;
    
    if (max_node == NULL)
        rc = ASSOC_ARRAY_NOT_FOUND;
    else
        *num = &(max_node->value);

    return rc;
}
