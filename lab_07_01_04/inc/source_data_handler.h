#ifndef SOURCE_DATA_H
#define SOURCE_DATA_H
#include "mode.h"
#include "error.h"
#include "stdio.h"

error_t load_and_read_source_file(const char *filename, int **src_array, int *array_length);
error_t sort_and_save_to_file(const char *destination_filename,
int *source_array, int source_length,
int *filtered_array_begin, int *filtered_array_end,
mode_t use_filter);

#endif