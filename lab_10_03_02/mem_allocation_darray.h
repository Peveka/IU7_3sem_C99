#ifndef MEM_ALLOCATION_DARRAY_H__
#define MEM_ALLOCATION_DARRAY_H__

#include <stddef.h>
#include "darray.h"

assoc_array_t array_alloc(void);
void array_free(assoc_array_t arr);

key_value_t *items_alloc(size_t capacity);
key_value_t *items_realloc(key_value_t *items, size_t new_capacity);
void items_free(key_value_t *items);

char *key_alloc(size_t size);
void key_free(char *key);

#endif