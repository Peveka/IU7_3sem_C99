#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#include "errors.h"
#include "data.h"

error_t struct_allocate(item_t **items_struct, int elem_count);
error_t name_allocate(char **name, int size);
void name_free(char **name);
void struct_free(item_t **items_struct, int struct_len);

#endif