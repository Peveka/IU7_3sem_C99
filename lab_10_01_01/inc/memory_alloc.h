#ifndef ALLOC_MEMORY_H__
#define ALLOC_MEMORY_H__

#include "list_struct.h"
#include "data.h"

void *alloc_elem(void);
void free_elem(node_t *elem);
footballer_t *footballer_alloc(const char *surname, int goals_count);
void footballer_free(footballer_t *fb);

#endif