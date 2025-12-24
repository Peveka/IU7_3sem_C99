#ifndef DARRAY_OPERATIONS_H__
#define DARRAY_OPERATIONS_H__

#include "associative_array.h"
#include "darray.h"

assoc_array_error_t delete_item(assoc_array_t arr, size_t index);
int find_key_index(const assoc_array_t arr, const char *key);
assoc_array_error_t arr_resize(assoc_array_t arr);

#endif