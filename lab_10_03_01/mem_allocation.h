#ifndef MEM_ALLOC_H__
#define MEM_ALLOC_H__
#include "stddef.h"
#include "list.h"
#include "associative_array.h"

assoc_array_t array_alloc(void);
assoc_array_error_t key_allocate(char **key, int key_size);
node_t *node_alloc(void);

void list_free(assoc_array_t list);
void node_free(node_t *node);
void key_free(char *key);

#endif