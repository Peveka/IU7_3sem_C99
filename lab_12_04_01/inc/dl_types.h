#ifndef DL_TYPES_H__
#define DL_TYPES_H__

#include "errors.h"

typedef error_t (*load_array_from_file_t)(const char *, int **, int *);
typedef error_t (*filter_array_t)(const int *, const int *, int *, int **);
typedef error_t (*sort_array_t)(int *, int *);
typedef error_t (*save_array_to_file_t)(const char *, const int *, const int *);

#endif