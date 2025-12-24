#include <stddef.h>
#include "errors.h"

error_t fill_fibonacci(int *array, size_t n, size_t *out_count) {
    if (!out_count || n < 0 || !out_count) 
        return ERR_FUNC_ARGS;
    
    *out_count = 0;
    if (n != 0)
    {
        array[0] = 0;
        if (n > 1) 
            array[1] = 1;

        for (size_t i = 2; i < n; ++i) 
            array[i] = array[i - 1] + array[i - 2];

        *out_count = n;
    }
    
    return OK;
}

static int is_in_arr(const int *array, size_t arr_size, int elem)
{
    int is_in_array_flag = 0;
    for (int i = 0; i < arr_size; ++i)
        if (array[i] == elem)
            is_in_array_flag = 1;
    return is_in_array_flag;
}

error_t add_unique_elements(const int *src, size_t src_size, int *dst, size_t *out_count) {
    if (!out_count || src_size < 0 || !dst || !out_count) 
        return ERR_FUNC_ARGS;
    
    *out_count = 0;    
    for (int i = 0; i < src_size; ++i)
        if (!is_in_arr(dst, *out_count, src[i]))
        {
            if (dst != NULL)
                dst[*out_count] = src[i];
            (*out_count)++;
        }

    return OK;
}