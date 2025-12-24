#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "sort.h"
#include "filter.h"
#include "file_io.h"
#include "memory.h"
#include "mode.h"

error_t load_and_read_source_file(const char *filename, int **src_array, int *array_length)
{
    if (filename == NULL || src_array == NULL || array_length == NULL || filename[0] == '\0')
        return ERROR_INVALID_DATA;

    error_t rc = OK;
    int file_opened_flag = 0;
    FILE *src_file = fopen(filename, "r");

    if (src_file == NULL)
        rc = ERROR_FILE_OPEN;
    else
        file_opened_flag = 1;

    if (rc == OK)
        rc = get_file_len(src_file, array_length);

    if (rc == OK)
        rc = allocate_memory_with_check(*array_length * sizeof(int), (void **)src_array);
    
    if (rc == OK)
        rc = read_file_digits(src_file, *src_array, *array_length);

    if (file_opened_flag)
        fclose(src_file);

    return rc;
}

error_t sort_and_save_to_file(const char *destination_filename,
int *source_array, int source_length,
int *filtered_array_begin, int *filtered_array_end,
mode_t use_filter)
{
    error_t rc = OK;

    if (destination_filename == NULL || destination_filename[0] == '\0' ||
        (use_filter != FILTER && use_filter != NO_FILTER))
    {
        rc = ERROR_INVALID_DATA;
    }
    else if (!use_filter)
    {
        if (source_array == NULL || source_length <= 0)
            rc = ERROR_INVALID_DATA;
        else
        {
            mysort(source_array, source_length, sizeof(int), cmp_int);
            rc = write_file_digits(destination_filename, source_array, source_length);
        }
    }
    else
    {
        if (filtered_array_begin == NULL || filtered_array_end == NULL ||
            filtered_array_end <= filtered_array_begin)
            rc = ERROR_INVALID_DATA;
        else
        {
            int filtered_length = filtered_array_end - filtered_array_begin;
            if (filtered_length <= 0)
                rc = ERROR_EMPTY_RESULT;
            else
            {
                mysort(filtered_array_begin, filtered_length, sizeof(int), cmp_int);
                rc = write_file_digits(destination_filename, filtered_array_begin, filtered_length);
            }
        }
    }

    return rc;
}