#ifndef FILTER_H__

#define FILTER_H__

static double get_average_value(const int *pb_src, const int *pe_src);
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
static int filter_func(int value, double average);
static int get_filtered_len(const int *start, const int *end);
int *move_digits_to_ar(const int *src, int src_len, int *dst);

#endif