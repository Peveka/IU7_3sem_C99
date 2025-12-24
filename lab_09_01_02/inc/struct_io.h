#ifndef STRUCT_IO_H__
#define STRUCT_IO_H__

#include <stdio.h>
#include "data.h"
#include "errors.h"
error_t analyze_data(const char *mass_line, const char *vol_line, double *mass, double *volume);
error_t handle_struct_scan(item_t **items, const char *filename, int *count_ptr);
void print_struct(item_t *items, int count);

#endif