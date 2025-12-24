#include <stdio.h>
#include <string.h>
#include "io.h"
#include "errors.h"
#include "struct.h"
#include "struct_sort.h"

static void strip_string(char *line)
{
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
    {
        line[len - 1] = '\0';
        len--;
    }
}

error_t file_read_line(FILE *file, char *line, size_t line_size)
{
    error_t rc = OK;
    if (!fgets(line, line_size, file))
        rc = ERROR_FILE_READ;

    if (rc == OK)
        strip_string(line);
    
    return !rc;
}