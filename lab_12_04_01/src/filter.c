#include "filter.h"
#include "errors.h"

static double get_average_value(const int *pb_src, const int *pe_src)
{
    double sum = 0.0;
    size_t count = pe_src - pb_src;
    if (count == 0) return 0.0;
    for (const int *p = pb_src; p < pe_src; ++p)
        sum += *p;
    return sum / count;
}

static int filter_func(int value, double average)
{
    return (double)value > average;
}

error_t key(const int *pb_src, const int *pe_src, int *dst_buffer, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || dst_buffer == NULL || pe_dst == NULL || pb_src >= pe_src)
        return ERROR_INVALID_DATA;

    double average = get_average_value(pb_src, pe_src);
    int *dst = dst_buffer;

    for (const int *src = pb_src; src < pe_src; ++src)
    {
        if (filter_func(*src, average))
            *dst++ = *src;
    }

    *pe_dst = dst;

    if (dst == dst_buffer)
        return ERROR_EMPTY_RESULT;

    return OK;
}