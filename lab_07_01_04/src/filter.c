#include <stdlib.h>
#include "filter.h"
#include "sort.h"
#include "errors.h"

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

static int filter_func(int value, double average)
{
    return ((double)value > average);
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

static int *move_digits_to_ar(const int *src, int src_len, int *dst, double average)
{
    int index = 0;
    for (int i = 0; i < src_len; ++i)
    {
        if (filter_func(*(src + i), average))
        {
            *(dst + index) = *(src + i);
            index++;
        }
    }

    return dst + index;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    error_t rc = OK;
    int src_len = 0;
    int filter_count = 0;
    int *temp_pb_dst = NULL;
    double average = 0;

    if (pb_src == NULL || pe_src == NULL || pb_dst == NULL || pe_dst == NULL)
        rc = ERROR_INVALID_DATA;

    if (rc == OK && pb_src >= pe_src)
        rc = ERROR_INVALID_DATA;

    if (rc == OK)
    {
        src_len = pe_src - pb_src;
        filter_count = get_filtered_len(pb_src, pe_src);

        if (filter_count <= 0)
            rc = ERROR_EMPTY_RESULT;
    }

    if (rc == OK)
    {
        temp_pb_dst = malloc(filter_count * sizeof(int));
        if (temp_pb_dst == NULL)
            rc = ERROR_MEMORY_ALLOCATION;
    }

    if (rc == OK)
    {
        average = get_average_value(pb_src, pe_src);
        *pe_dst = move_digits_to_ar(pb_src, src_len, temp_pb_dst, average);
        *pb_dst = temp_pb_dst;
        temp_pb_dst = NULL;
    }

    if (temp_pb_dst != NULL)
    {
        free(temp_pb_dst);
        temp_pb_dst = NULL;
    }

    if (rc != OK)
    {
        if (pb_dst != NULL)
            *pb_dst = NULL;
        if (pe_dst != NULL)
            *pe_dst = NULL;
    }

    return rc;
}