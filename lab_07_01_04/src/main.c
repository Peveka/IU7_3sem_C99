#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "file_io.h"
#include "sort.h"
#include "mode.h"
#include "filter.h"
#include "memory.h"
#include "source_data_handler.h"

int main(int argc, char **argv)
{
    error_t rc = args_handle(argc);
    mode_t filter_mode = mode_define(argc, argv);

    if (filter_mode == UNKNOWN_MODE)
        rc = ERROR_UNKNOWN_MODE;

    int array_length = 0;
    int *source_array = NULL;
    int *filtered_array_begin = NULL;
    int *filtered_array_end = NULL;
    if (rc == OK)
        rc = load_and_read_source_file(argv[1], &source_array, &array_length);

    if (rc == OK && filter_mode == FILTER)
        rc = key(source_array, source_array + array_length, &filtered_array_begin, &filtered_array_end);

    if (rc == OK)
        rc = sort_and_save_to_file(argv[2], source_array, array_length, filtered_array_begin, filtered_array_end, filter_mode);
        
    free_memory((void **)&source_array);
    free_memory((void **)&filtered_array_begin);

    return rc;
}