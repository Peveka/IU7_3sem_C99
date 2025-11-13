#ifndef LIST_SORT_H__
#define LIST_SORT_H__

#include "list_struct.h"

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));
node_t *sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

#endif