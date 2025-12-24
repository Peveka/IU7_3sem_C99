#ifndef LIST_H__
#define LIST_H__
#include "associative_array.h"

typedef struct node_t node_t;

struct node_t
{
    char *key;
    int value;
    node_t *next;
};

struct assoc_array_type
{
    node_t *head;
};

assoc_array_error_t delete_node(assoc_array_t arr, node_t *node_to_delete);
assoc_array_error_t create_node(node_t *node, const char *key, int value); 
node_t *list_search(const assoc_array_t list, const char *key);

#endif