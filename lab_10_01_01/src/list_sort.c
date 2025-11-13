#include "list_struct.h"
#include "alloc_memory.h"
#include <string.h>

node_t *sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    node_t *result = NULL;
    if (head != NULL && element != NULL && comparator != NULL)
    {
        node_t **current_ptr = head;
        int found_necessary_position = 0;
        while (*current_ptr != NULL && found_necessary_position == 0)
            if (comparator(element->data, (*current_ptr)->data) <= 0)
                found_necessary_position = 1;
            else
                current_ptr = &(*current_ptr)->next;
        
        element->next = *current_ptr;
        *current_ptr = element;
        result = *head;
    }
    
    return result;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *sorted = NULL;
    node_t *node = head;
    
    while (node != NULL)
    {
        node_t *next_node = node->next;
        sorted_insert(&sorted, node, comparator);
        node = next_node;
    }
    
    return sorted;
}