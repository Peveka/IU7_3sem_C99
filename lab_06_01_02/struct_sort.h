#ifndef STRUCT_SORT_H__
#define STRUCT_SORT_H__

#include "data.h"
#define DBL_EPSILON 2.220446049250313080847e-16
int compare_double(double a, double b, double epsilon);
void sort_struct(item_t *items, int count);

#endif