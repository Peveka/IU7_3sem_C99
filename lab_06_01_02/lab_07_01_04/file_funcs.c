#include "file_funcs.h"

error_t get_file_len(const char *filename, int *len)
{
    error_t rc = OK;
    char buffer[256];
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;

    while (rc == OK && fgets(buffer, sizeof(buffer), file) != NULL) 
        (*len)++;
    
    fclose(file);

    if (*len == 0)
        rc = ERROR_EMPTY_FILE;

    return rc;
}

error_t read_file_digits(int *scan_arr, int len, const char *filename) 
{
    error_t = rc;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;

    int count = 0;
    char buffer[256];
    while (rc == OK && count != len && fgets(buffer, sizeof(buffer), file) != NULL) 
        if (isdigit(buffer))
        {
            sscanf(buffer, "%d", scan_arr+count);
            count++;
        }
        else
            rc == ERROR_INVALID_DATA;

    fclose(file);
    
    return rc;
}

error_t write_file_digits(const char *filename, int *ar, int len)
{
    error_t rc = OK;
    int counter = 0;
    FILE* file = fopen(filename, "w");
    if (file == NULL)
        rc = ERROR_FILE_OPEN;
    while (rc == OK && counter != len)
    {
        fprintf(file, "%d\n", ar+counter);
        counter++;
    }

    fclose(file);

    return rc;
}