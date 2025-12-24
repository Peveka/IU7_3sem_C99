#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "file_funcs.h"

error_t get_file_len(FILE *file, int *len)
{
    if (!file || !len)
        return ERROR_INVALID_DATA;

    error_t rc = OK;
    int scanned_num = 0;

    if (fscanf(file, "%d", &scanned_num) != 1)
        rc = ERROR_EMPTY_FILE;
    else
    {
        (*len)++;

        while (rc == OK && fscanf(file, "%d", &scanned_num) == 1)
            (*len)++;

        if (!feof(file))
            rc = ERROR_INVALID_DATA;
    }

    fseek(file, 0, SEEK_SET);

    return rc;
}

error_t read_file_digits(int *scan_arr, int len, const char *filename) 
{
    error_t rc = OK;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        return ERROR_FILE_OPEN;

    for (int i = 0; i < len && rc == OK; ++i)
    {
        if (fscanf(file, "%d", scan_arr + i) != 1)
            rc = ERROR_INVALID_DATA;
    }

    fclose(file);
    
    return rc;
}

error_t write_file_digits(const char *filename, int *ar, int len)
{
    error_t rc = OK;
    FILE* file = fopen(filename, "w");
    if (file == NULL)
        return ERROR_FILE_OPEN;
        
    for (int i = 0; i < len && rc == OK; i++)
    {
        if (fprintf(file, "%d ", *(ar + i)) < 0)
            rc = ERROR_FILE_OPEN;
    }

    fclose(file);
    return rc;
}
