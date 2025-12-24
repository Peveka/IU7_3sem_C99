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
    if (!head || *head == NULL) 
        return;

    node_t *current = *head;
    node_t *next_node;
    
    while (current != NULL)
    {
        next_node = current->next;
        footballer_free((footballer_t*)current->data);
        free_elem(current);                            
        
        current = next_node;
    }
    *head = NULL;
}

void remove_duplicated(node_t **head, comparator_ptr comparator)
{
    if (!head || !*head || !comparator) 
        return;
    
    node_t *current = *head;
    
    while (current != NULL)
    {
        node_t *runner = current;
        
        while (runner->next != NULL)
        {
            if (comparator(current->data, runner->next->data))
            {
                node_t *duplicate = runner->next;
                runner->next = duplicate->next;
                footballer_free((footballer_t*)duplicate->data);
                free_elem(duplicate);
            }
            else
            {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

error_t list_filter(node_t **head, int min_goal_count)
{
    if (!head || !*head)
        return ERR_INVALID_DATA;
    
    node_t *current = *head;
    node_t *prev = NULL;

    while (current != NULL)
    {
        footballer_t *fb = (footballer_t*)current->data;
        
        if (fb->goals_count < min_goal_count)
        {
            node_t *to_delete = current;
            current = current->next;           
            if (to_delete == *head)
            {
                delete_elem(head, to_delete);
            }
            else
            {
                prev->next = current; 
                footballer_free((footballer_t*)to_delete->data);
                free_elem(to_delete);
            }
        }
        else
        {
            prev = current;
            current = current->next;
        }
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