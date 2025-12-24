#ifndef LIST_OPERATIONS_H__
#define LIST_OPERATIONS_H__

#include "data.h"
#include "errors.h"

error_t create_node(polynom_t **node, int degree_value);
error_t add_node(polynom_t **polynome, polynom_t *node);
error_t remove_list(polynom_t **polynome);
int calculate_list_size(polynom_t *polynome);

#endif