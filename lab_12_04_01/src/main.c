#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "mode.h"
#include "memory.h"

#if defined(STATIC_LIB)
    #include "array_processor.h"
#elif defined(DYNAMIC_LOAD)
    #include <dlfcn.h>
    #include "dl_types.h"
    #define LIB_PATH "./libs/libarrayproc.so"
#elif defined(DYNAMIC_LINK)
    #include "array_processor.h"
#else
    #error "Режим работы программы должен быть обьявлен соответствующим ключем при компиляции! (STATIC_LIB, DYNAMIC_LINK, DYNAMIC_LOAD)"
#endif

#if defined(DYNAMIC_LOAD)
static error_t load_library_functions(void *handle, load_array_from_file_t *load_func, filter_array_t *filter_func, sort_array_t *sort_func, save_array_to_file_t *save_func)
{
    error_t rc = OK;
    *(void **)load_func = dlsym(handle, "load_array_from_file");
    if (dlerror() != NULL)
        rc = ERR_UNIT_FAIL;

    if (rc == OK)
    {
        *(void **)filter_func = dlsym(handle, "filter_array");
        if (dlerror() != NULL)
            rc = ERR_UNIT_FAIL;
    }

    if (rc == OK)
    {
        *(void **)sort_func = dlsym(handle, "sort_array");
        if (dlerror() != NULL)
            rc = ERR_UNIT_FAIL;
    }

    if (rc == OK)
    {
        *(void **)save_func = dlsym(handle, "save_array_to_file");
        if (dlerror() != NULL)
            rc = ERR_UNIT_FAIL;
    }

    return rc;
}
#endif

int main(int argc, char **argv)
{
    error_t rc = OK;
    mode_t filter_mode = NO_FILTER;
    int *source_array = NULL, *filtered_buffer = NULL, *result_begin = NULL, *result_end = NULL;
    int source_len = 0;

 #if defined(DYNAMIC_LOAD)
    void *handle = NULL;
    load_array_from_file_t load_array_from_file = NULL;
    filter_array_t filter_array = NULL;
    sort_array_t sort_array = NULL;
    save_array_to_file_t save_array_to_file = NULL;
#endif

    rc = args_handle(argc);
    
    if (rc == OK)
    {
        filter_mode = mode_define(argc, argv);
        if (filter_mode == UNKNOWN_MODE)
            rc = ERROR_UNKNOWN_MODE;
    }

#if defined(DYNAMIC_LOAD)
    if (rc == OK)
    {
        handle = dlopen(LIB_PATH, RTLD_LAZY);
        if (handle == NULL)
            rc = ERR_UNIT_FAIL;
    }
        
    if (rc == OK)
        rc = load_library_functions(handle, &load_array_from_file, &filter_array, &sort_array, &save_array_to_file);
#endif

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

#if defined(DYNAMIC_LOAD)
    if (handle != NULL)
        dlclose(handle);
#endif

    return rc;
}