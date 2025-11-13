#ifndef OPERATIONS_WITH_LIST_H__
#define OPERATIONS_WITH_LIST_H__

#include "list_struct.h"
#include "errors.h"

void list_init(node_t **head);
void list_delete(node_t **head);
void remove_duplicated(node_t **head, comparator_ptr comparator);
error_t list_filter(node_t **head, int min_goal_count);
error_t add_node_to_list(node_t **head, node_t *new_node);

#endif