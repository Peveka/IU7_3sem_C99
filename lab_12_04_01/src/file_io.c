#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "file_io.h"
#include "errors.h"

error_t get_file_len(FILE *file, int *len)
{
    error_t rc = OK;
    int scanned_num = 0;

    if (*len < 0 || file == NULL)
        rc = ERROR_INVALID_DATA;

    if (rc == OK && fscanf(file, "%d", &scanned_num) != 1)
        rc = ERROR_EMPTY_FILE;
    
    if (rc == OK)
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

error_t read_file_digits(FILE *file, int *scan_arr, int len) 
{
    error_t rc = OK;

    if (len <= 0 || file == NULL || scan_arr == NULL)
        rc = ERROR_INVALID_DATA;

    for (int i = 0; i < len && rc == OK; ++i)
    {
        if (fscanf(file, "%d", scan_arr + i) != 1)
            rc = ERROR_INVALID_DATA;
    }
    
    return rc;
}

error_t write_file_digits(const char *filename, int *ar, int len)
{
    error_t rc = OK;
    FILE* file = fopen(filename, "w");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;
    
    if (ar == NULL || len <= 0)
        rc = ERROR_INVALID_DATA;

    for (int i = 0; i < len && rc == OK; i++)
    {
        if (fprintf(file, "%d ", *(ar + i)) < 0)
            rc = ERROR_FILE_OPEN;
    }

    fclose(file);
    return rc;
}
