#ifndef FILTER_H__
#define FILTER_H__

#include "errors.h"

error_t key(const int *pb_src, const int *pe_src, int *dst_buffer, int **pe_dst);

#endif