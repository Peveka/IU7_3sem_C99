#ifndef STRUCT_H__

#define STRUCT_H__
#include <stdio.h>
#include "data.h"
#include "errors.h"
#define DBL_EPSILON 2.220446049250313080847e-16

int compare_double(double a, double b, double epsilon);
void swap_items(item_t *a, item_t *b);
void append_struct_item(double mass, double volume, const char *line, int indx, item_t *items);
void scan_struct(error_t *rc, int *indx, FILE *file, item_t *items);
error_t handle_struct_scan(item_t *items, const char *filename, int *count_ptr);
void sort_struct(item_t *items, int count);
error_t search_string(item_t *items, int count, const char *prefix);

#endif