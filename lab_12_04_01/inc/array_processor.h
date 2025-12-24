#ifndef ARRAY_PROCESSOR_H__
#define ARRAY_PROCESSOR_H__

#include "errors.h"

error_t load_array_from_file(const char *filename, int **array, int *length);

error_t filter_array(const int *src_begin, const int *src_end,
                     int *dst_buffer,
                     int **dst_end);

error_t sort_array(int *begin, int *end);

error_t save_array_to_file(const char *filename, const int *begin, const int *end);

#endif