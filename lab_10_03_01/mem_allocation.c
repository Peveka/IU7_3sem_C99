#include <string.h>
#include <stdlib.h>
#include "mem_allocation.h"
#include "list.h"
#include "associative_array.h"

assoc_array_t array_alloc(void)
{
    return malloc(sizeof(struct assoc_array_type));
}

node_t *node_alloc(void)
{
    return malloc(sizeof(node_t));
}

assoc_array_error_t key_allocate(char **key, int key_size)
{
    if (key == NULL || key_size <= 0)
        return ASSOC_ARRAY_INVALID_PARAM;
    *key = malloc(key_size*sizeof(char));
    return (*key != NULL) ? ASSOC_ARRAY_OK : ASSOC_ARRAY_MEM;
}

void list_free(assoc_array_t list)
{
    if (list == NULL)
        return;
    for (node_t *cur_node = list->head; cur_node != NULL;)
    {
        node_t *free_node = cur_node;
        cur_node = cur_node->next;
        node_free(free_node);
    }
    list->head = NULL;
}

void key_free(char *key)
{
    free(key);
}

void node_free(node_t *node)
{
    key_free(node->key);
    free(node);
}