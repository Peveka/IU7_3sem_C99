#ifndef SORT_H__

#define SORT_H__
#include <stdlib.h>
typedef int (*compare_func_t)(const void *, const void *);
int cmp_int(const void *num1, const void *num2);
void mysort(void *base, size_t num, size_t size, int (*compare)(const void *, const void *));

#endif