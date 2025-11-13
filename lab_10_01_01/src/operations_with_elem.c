#include "list_struct.h"
#include "alloc_memory.h"
#include "errors.h"
error_t create_footballer_node(const char *surname, int goals, node_t **new_node)
{
    error_t rc = OK;
    footballer_t *fb = NULL;
    node_t *node = NULL;
    fb = footballer_alloc(surname, goals);
    if (fb == NULL)
        rc = ERR_NOT_ENOUGH_DATA;
    
    if (rc == OK)
    {
        node = malloc(sizeof(node_t));
        if (node == NULL)
        {
            footballer_free(fb);
            rc = ERR_NOT_ENOUGH_DATA;
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
    int should_delete_flag = 1;
    if (*head == elem)
    {
        *head = elem->next;
        free_elem(elem);
        should_delete_flag = 0;
    }
    for (node_t *cur = *head; should_delete_flag && cur != NULL; cur = cur->next)
    {
        if (cur->next == elem)
        {
            cur->next = elem->next;
            free_elem(elem);
            should_delete_flag = 0;
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