#include "data.h"
#include "errors.h"
#include "mem_allocation.h"
#include <stdlib.h>

error_t create_node(polynom_t **node, int degree_value)
{
    error_t rc = OK;
    rc = node_alloc(node);
    if (rc == OK)
    {
        (*node)->next = NULL;
        (*node)->degree_value = degree_value;
    }

    return rc;
}

error_t add_node(polynom_t **polynome, polynom_t *node)
{
    if (!node)
        return ERR_ARGS_DATA;
        
    if (!*polynome)
        *polynome = node;
    else
    {
        polynom_t *current_node = *polynome;
        while (current_node->next != NULL)
            current_node = current_node->next;
        current_node->next = node;
    }

    return OK;
}

error_t remove_list(polynom_t **polynome)
{
    if (!polynome)
        return ERR_ARGS_DATA;
        
    polynome_free(polynome);
    return OK;
}

int calculate_list_size(polynom_t *polynome)
{
    int size = 0;
    polynom_t *current = polynome;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}
