#ifndef SORT_H__

#define SORT_H__
#include <stdlib.h>

int cmp_int(const void *num1, const void *num2);
void swap_items(void *el1, void *el2, size_t elem_size);
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));

#endif