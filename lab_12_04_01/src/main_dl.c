#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "errors.h"
#include "mode.h"
#include "memory.h"
#include "dl_types.h"
#define LIB_PATH "./libs/libarrayproc.so"

static error_t load_library_functions(void *handle, load_array_from_file_t *load_func, filter_array_t *filter_func, sort_array_t *sort_func, save_array_to_file_t *save_func)
{
    error_t rc = OK;
    
    *load_func = (load_array_from_file_t)dlsym(handle, "load_array_from_file");
    if (dlerror() != NULL)
        rc = ERR_UNIT_FAIL;

    if (rc == OK)
    {
        *filter_func = (filter_array_t)dlsym(handle, "filter_array");
        if (dlerror() != NULL)
            rc = ERR_UNIT_FAIL;
    }

    if (rc == OK)
    {
        *sort_func = (sort_array_t)dlsym(handle, "sort_array");
        if (dlerror() != NULL)
            rc = ERR_UNIT_FAIL;
    }

    if (rc == OK)
    {
        *save_func = (save_array_to_file_t)dlsym(handle, "save_array_to_file");
        if (dlerror() != NULL)
            rc = ERR_UNIT_FAIL;
    }

    return rc;
}

int main(int argc, char **argv)
{
    error_t rc = OK;
    mode_t filter_mode = NO_FILTER;
    int *source_array = NULL, *filtered_buffer = NULL, *result_begin = NULL, *result_end = NULL;
    int source_len = 0;
    void *handle = NULL;

    load_array_from_file_t load_array_from_file = NULL;
    filter_array_t filter_array = NULL;
    sort_array_t sort_array = NULL;
    save_array_to_file_t save_array_to_file = NULL;

    handle = dlopen(LIB_PATH, RTLD_LAZY);
    if (handle == NULL)
        rc = ERR_UNIT_FAIL;

    if (rc == OK)
        rc = load_library_functions(handle, &load_array_from_file, &filter_array, &sort_array, &save_array_to_file);
    if (rc == OK)
        rc = args_handle(argc);
    
    if (rc == OK)
    {
        filter_mode = mode_define(argc, argv);
        if (filter_mode == UNKNOWN_MODE)
            rc = ERROR_UNKWN_MODE;
    }

    if (rc == OK)
        rc = load_array_from_file(argv[1], &source_array, &source_len);

    result_begin = source_array;
    result_end = source_array + source_len;

    if (rc == OK && filter_mode == FILTER)
        rc = allocate_memory_with_check(source_len * sizeof(int), (void **)&filtered_buffer);

    if (rc == OK && filter_mode == FILTER)
        rc = filter_array(source_array, source_array + source_len, filtered_buffer, &result_end);

    if (rc == OK && filter_mode == FILTER)
        result_begin = filtered_buffer;

    if (rc == OK)
        rc = sort_array(result_begin, result_end);

    if (rc == OK)
        rc = save_array_to_file(argv[2], result_begin, result_end);

    free_memory((void **)&source_array);
    free_memory((void **)&filtered_buffer);

    if (handle != NULL)
        dlclose(handle);

    return rc;
}