#ifndef MEM_ALLOCATION_H__
#define MEM_ALLOCATION_H__

#include "data.h"
#include "errors.h"

error_t node_alloc(polynom_t **node);
error_t polynome_free(polynom_t **head);
error_t alloc_coef_array(int **coeffs_arr, int data_count);
void free_coef_data(int **coef_arr);

#endif