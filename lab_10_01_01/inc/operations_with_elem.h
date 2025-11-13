#ifndef OPERATIONS_WITH_ELEM_H__
#define OPERATIONS_WITH_ELEM_H__
#include "errors.h"
#include "list_struct.h"

error_t create_footballer_node(const char *surname, int goals, node_t **new_node);
void delete_elem(node_t **head, node_t *elem);
node_t *find(node_t *head, const void *data, comparator_ptr comparator);
void *pop_front(node_t **head);

#endif