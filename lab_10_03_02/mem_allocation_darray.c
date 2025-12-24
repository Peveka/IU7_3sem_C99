#include <stdlib.h>
#include "mem_allocation_darray.h"

assoc_array_t array_alloc(void)
{
    return malloc(sizeof(struct assoc_array_type));
}

void array_free(assoc_array_t arr)
{
    free(arr);
}

key_value_t *items_alloc(size_t capacity)
{
    return malloc(capacity * sizeof(key_value_t));
}

key_value_t *items_realloc(key_value_t *items, size_t new_capacity)
{
    return realloc(items, new_capacity * sizeof(key_value_t));
}

void items_free(key_value_t *items)
{
    free(items);
}

char *key_alloc(size_t size)
{
    return malloc(size * sizeof(char));
}

void key_free(char *key)
{
    free(key);
}