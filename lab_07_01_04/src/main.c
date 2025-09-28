#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "file_funcs.h"
#include "sort.h"
#include "mode.h"
#include "filter.h"

int main(int argc, char **argv) 
{
    error_t rc = OK;
    rc = args_handle(argc);
    mode_t filter_flag = mode_define(argc, argv); 
    
    if (filter_flag == UNKNOWN_MODE)
        rc = ERROR_UNKWN_MODE;

    const char *src_filename;
    const char *dest_filename;
    int len = 0;

    if (rc == OK)
    {
        src_filename = argv[1];
        dest_filename = argv[2];
        rc = get_file_len(src_filename, &len); 
    }

    int *src_ar = NULL;
    int *filt_ar_begin = NULL;
    int *filt_ar_end = NULL;
    
    if (rc == OK)
    {
        src_ar = malloc(len * sizeof(int));
        if (src_ar == NULL)
            rc = ERROR_MEMORY_ALLOCATION;
    }

    if (rc == OK)
        rc = read_file_digits(src_ar, len, src_filename);

    if (filter_flag && rc == OK)
        rc = key(src_ar, src_ar + len, &filt_ar_begin, &filt_ar_end);

    if (rc == OK)
    {
        if (filter_flag)
        {
            mysort(filt_ar_begin, filt_ar_end - filt_ar_begin, sizeof(int), cmp_int);
            rc = write_file_digits(dest_filename, filt_ar_begin, filt_ar_end - filt_ar_begin);
        }
        else
        {
            mysort(src_ar, len, sizeof(int), cmp_int);
            rc = write_file_digits(dest_filename, src_ar, len);
        }
    }

    free(src_ar);
    free(filt_ar_begin);
    return rc;
}