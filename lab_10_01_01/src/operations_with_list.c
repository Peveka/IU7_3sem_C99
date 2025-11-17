#include <string.h>
#include "list_struct.h"
#include "alloc_memory.h"
#include "data.h"
#include "operations_with_elem.h"
#include "errors.h"

void list_init(node_t **head)
{
    *head = NULL;
}

void list_delete(node_t **head)
{
    if (!head) 
        return;
    for(node_t *cur_elem = *head; cur_elem; )
    {
        node_t *prev_elem = cur_elem;
        cur_elem = cur_elem->next;
        footballer_free((footballer_t*)prev_elem->data);
        
        free_elem(prev_elem); 
    }
    *head = NULL;
}

void remove_duplicated(node_t **head, comparator_ptr comparator)
{
    if (!head || !*head || !comparator)
        return;
    node_t *cur_elem = *head;
    for (;cur_elem; cur_elem=cur_elem->next)
        for (node_t *next_elem = cur_elem->next; next_elem;)
        {
            if (comparator(cur_elem->data, next_elem->data) == 0)
            {
                node_t *dublicate_elem = next_elem;
                next_elem = next_elem->next;
                delete_elem(head, dublicate_elem);
            }
            else
                next_elem = next_elem->next;
        }          
}

error_t list_filter(node_t **head, int min_goal_count)
{
    if (!head || !*head)
        return ERR_INVALID_DATA;
    for (node_t *current = *head; current != NULL;)
    {
        footballer_t *fb = (footballer_t*)current->data;
        node_t *next = current->next;
        
        if (fb->goals_count < min_goal_count)
            delete_elem(head, current);
        current = next;
    }
    
    return OK;
}

error_t add_node_to_list(node_t **head, node_t *new_node)
{
    error_t rc = OK;
    
    if (head == NULL || new_node == NULL)
        return ERR_INVALID_DATA;
        
    if (*head == NULL)
        *head = new_node;
    else
    {
        node_t *current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
    
    new_node->next = NULL;
    
    return rc;
}