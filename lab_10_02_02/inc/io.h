#ifndef IO_H__
#define IO_H__
#include "errors.h"

error_t scan_mode(char *mode);
error_t scan_polynome_coefficients(int **coef_array, int *coeffs_count);
error_t output_polynome_coeffs(int *polynome_coeffs, int polynome_size);
error_t output_evaluate_value(int value);
error_t scan_evaluate_value(int *input_value);

#endif