#include <stdio.h>
#include "errors.h"
#include "mode.h"
#include "array_processor.h"
#include "memory.h"

int main(int argc, char **argv)
{
    error_t rc = args_handle(argc);
    mode_t filter_mode = NO_FILTER;
    int *source_array = NULL, *filtered_array = NULL, *result_begin = NULL, *result_end = NULL;
    int source_len = 0;

    if (rc == OK)
    {
        filter_mode = mode_define(argc, argv);
        if (filter_mode == UNKNOWN_MODE)
            rc = ERROR_UNKNOWN_MODE;
    }

    if (rc == OK)
        rc = load_array_from_file(argv[1], &source_array, &source_len);

    result_begin = source_array;
    result_end = source_array + source_len;

    if (rc == OK && filter_mode == FILTER)
        rc = allocate_memory_with_check(source_len * sizeof(int), (void **)&filtered_array);

    if (rc == OK && filter_mode == FILTER)
        rc = filter_array(source_array, source_array + source_len, filtered_array, &result_end);

    if (rc == OK && filter_mode == FILTER)
        result_begin = filtered_array;

    if (rc == OK)
        rc = sort_array(result_begin, result_end);

    if (rc == OK)
        rc = save_array_to_file(argv[2], result_begin, result_end);

    free_memory((void **)&source_array);
    free_memory((void **)&filtered_array);

    return rc;
}