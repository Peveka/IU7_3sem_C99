#ifndef DARRAY_H__
#define DARRAY_H__

#include "associative_array.h"

typedef struct key_value_t key_value_t;

struct key_value_t
{
    char *key;
    int value;
};

struct assoc_array_type
{
    key_value_t *items;
    size_t size;
    size_t capacity;
};

assoc_array_error_t delete_item(assoc_array_t arr, size_t index);
int find_key_index(const assoc_array_t arr, const char *key);
assoc_array_error_t arr_resize(assoc_array_t arr);

#endif