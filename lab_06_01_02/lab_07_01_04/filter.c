#include "filter.h"
#include "sort.h"

static double get_average_value(const int *pb_src, const int *pe_src)
{
    double sum = 0;
    int count = 0;
    for (const int *p = pb_src; p < pe_src; p++)
    {
        sum += *p;
        count++;
    }
    return count > 0 ? sum / count : 0;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int rc = 1;
    const int *src_start_pointer = pb_src;
    if (!pb_src || !pe_src || !pb_dst || !pe_dst || pb_src > pe_src) {
        rc = 0;
    }

    int filter_count = 0;
    if (rc == 1)
        filter_count = get_filtered_len(pb_src, pe_src);

    if (filter_count != 0)
        *pb_dst = malloc(filter_count*sizeof(int));
    else
        rc = 0;

    if (*pb_dst == NULL)
        rc = 0;

    if (rc == 1)
        *pe_dst = move_digits_to_ar(pb_src, pe_dst-pb_dst, *pb_dst);

    return rc;
}

static int filter_func(int value, double average)
{
    return (double(value)-average > 0 ? 1 : 0);
}

static int get_filtered_len(const int *start, const int *end)
{
    int count = 0;
    double average = get_average_value(start, end);
    for (const int *ptr = start; ptr < end; ++ptr)
    {
        if (filter_func(*ptr, average))
            count++;
    }

    return count;
}

int *move_digits_to_ar(const int *src, int src_len, int *dst)
{
    int index = 0;
    double average = get_average_value(src, src+src_len);
    for(int i = 0; i < src_len; ++i)
        if (filter_func(*(src+i), average))
        {
            *(dst + index) = *(src+i);
            index++;
        }

    return dst+index;
}