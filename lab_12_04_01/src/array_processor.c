// src/array_processor.c
#include "array_processor.h"
#include "file_io.h"
#include "filter.h"
#include "sort.h"
#include "memory.h"
#include <stdio.h>

error_t load_array_from_file(const char *filename, int **array, int *length)
{
    if (!filename || !array || !length)
        return ERROR_INVALID_DATA;
    error_t rc = OK;
    FILE *file = NULL;
    int temp_len = 0;   

    *array = NULL;
    *length = 0;

    file = fopen(filename, "r");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;

    if (rc == OK)
        rc = get_file_len(file, &temp_len);

    if (rc == OK)
        rc = allocate_memory_with_check(temp_len * sizeof(int), (void **)array);

    if (rc == OK)
        rc = read_file_digits(file, *array, temp_len);

    if (rc == OK)
        *length = temp_len;
    else
    {
        free_memory((void **)array);
        *array = NULL;
    }

    if (file != NULL)
        fclose(file);

    return rc;
}

error_t filter_array(const int *src_begin, const int *src_end,
                     int *dst_buffer, int **dst_end)
{
    error_t rc = OK;

    if (dst_end != NULL)
        *dst_end = dst_buffer;

    if (src_begin == NULL || src_end == NULL || dst_buffer == NULL || dst_end == NULL)
        rc = ERROR_INVALID_DATA;

    if (rc == OK && src_begin >= src_end)
        rc = ERROR_INVALID_DATA;

    if (rc == OK)
        rc = key(src_begin, src_end, dst_buffer, dst_end);

    return rc;
}

error_t sort_array(int *begin, int *end)
{
    if (begin == NULL || end == NULL || begin >= end)
        return ERROR_INVALID_DATA;
    
    mysort(begin, end - begin, sizeof(int), cmp_int);

    return OK;
}

error_t save_array_to_file(const char *filename, const int *begin, const int *end)
{
    if (!filename || !begin || !end || begin >= end)
        return ERROR_INVALID_DATA;

    return write_file_digits(filename, (int *)begin, end - begin);
}