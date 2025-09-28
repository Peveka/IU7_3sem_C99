#ifndef FUNCS_H__

#define FUNCS_H__
#include <stdio.h>
#include <string.h>
#include "errors.h"

error_t get_file_len(const char *filename, int *len);
error_t read_file_digits(int *scan_arr, int len, const char *filename);
error_t write_file_digits(const char *filename, int *ar, int len);


#endif