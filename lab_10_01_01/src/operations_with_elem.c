#include <stddef.h>
#include "list_struct.h"
#include "alloc_memory.h"
#include "errors.h"

error_t create_footballer_node(const char *surname, int goals, node_t **new_node)
{
    if (!surname || goals < 0 || !new_node)
        return ERR_INVALID_DATA;
    error_t rc = OK;
    footballer_t *fb = NULL;
    node_t *node = NULL;

    fb = footballer_alloc(surname, goals);
    if (fb == NULL)
        rc = ERR_MEM_ALLOC;
    
    if (rc == OK)
    {
        node = node_alloc(); 
        if (node == NULL)
        {
            footballer_free(fb);
            rc = ERR_MEM_ALLOC;
        }
    }

    if (rc == OK)
    {
        node->data = fb;
        node->next = NULL;
        *new_node = node;
    }
    
    return rc;
}

void delete_elem(node_t **head, node_t *elem)
{
    if (!head || *head == NULL || !elem)
        return;
        
    if (*head == elem)
    {
        *head = elem->next;
        footballer_free((footballer_t*)elem->data);
        free_elem(elem);
    }
    else
    {
        node_t *current = *head;
        while (current->next != NULL && current->next != elem)
            current = current->next;
        
        if (current->next == elem)
        {
            current->next = elem->next;
            footballer_free((footballer_t*)elem->data);
            free_elem(elem);
        }
    }
}

node_t *find(node_t *head, const void *data, comparator_ptr comparator)
{
    node_t *desired_elem = NULL;
    if (!head || !data || !comparator)
        return desired_elem;
    node_t *current_item = head;
    for (;desired_elem == NULL && current_item; current_item = current_item->next)
    {
        if (comparator(current_item->data, data) == 0)
            desired_elem = current_item;
    }

    return desired_elem;
}

void *pop_front(node_t **head)
{
    if (head == NULL || *head == NULL)
        return NULL;
    
    node_t *popped_elem = *head;
    void *data = popped_elem->data;
    
    *head = (*head)->next;
    free_elem(popped_elem);
    
    return data;
}
