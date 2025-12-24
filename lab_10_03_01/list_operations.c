#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "associative_array.h"
#include "mem_allocation.h"

assoc_array_error_t create_node(node_t *node, const char *key, int value)
{
    if (node == NULL || key == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    assoc_array_error_t rc = key_allocate(&(node->key), strlen(key) + 1);
    if (rc == ASSOC_ARRAY_OK)
    {
        strcpy(node->key, key);
        node->value = value;
        node->next = NULL;
    }
    
    return rc;
}

node_t *list_search(const assoc_array_t list, const char *key)
{
    int should_search_flag = 1;
    node_t *finded_elem = NULL;
    for (node_t *current_node = list->head; should_search_flag && current_node != NULL; current_node = current_node->next)
    {
        if (strcmp(current_node->key, key) == 0)
        {
            should_search_flag = 0;
            finded_elem = current_node;
        }
    }

    return finded_elem;
}

assoc_array_error_t delete_node(assoc_array_t arr, node_t *node_to_delete)
{
    if (arr == NULL || node_to_delete == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    assoc_array_error_t rc = ASSOC_ARRAY_OK;    
    if (arr->head == node_to_delete)
    {
        node_t *removed_node = arr->head;
        arr->head = arr->head->next;
        node_free(removed_node);
    }
    else
    {
        node_t *current_node = arr->head->next;
        node_t *prev_node = arr->head;
        int should_search_flag = 1;
        for (; should_search_flag && current_node != NULL;)
        {
            if (current_node == node_to_delete)
            {
                should_search_flag = 0;
                prev_node->next = current_node->next;
                node_free(current_node);
            }
            else
            {
                prev_node = current_node;
                current_node = current_node->next;
            }
        }

        if (should_search_flag == 1)
            rc = ASSOC_ARRAY_NOT_FOUND;
    }

    return rc;
}