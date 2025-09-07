#include <stdio.h>
#include <string.h>
#include "io.h"
#include "errors.h"
#include "struct.h"

int file_read_line(FILE *file, char *line, size_t line_size)
{
    if (!fgets(line, line_size, file))
        return 0;

    size_t len = strlen(line);
    
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) 
    {
        line[len - 1] = '\0';
        len--;
    }

    return 1;
}

error_t analyze_data(const char *mass_line, const char *vol_line, double *mass, double *volume)
{
    error_t rc = OK;
    int mass_scanned = sscanf(mass_line, "%lf", mass);
    int vol_scnned = sscanf(vol_line, "%lf", volume) != 1;
    if (mass_scanned == 1 || vol_scnned == 1)
    {
        int mass_valid = compare_double(*mass, 0.0, DBL_EPSILON);
        int vol_valid = compare_double(*volume, 0.0, DBL_EPSILON);
        if (vol_valid <= 0 || mass_valid <= 0)
            rc = ERROR_INVALID_DATA;
    }
    else
    {
        rc = ERROR_INVALID_DATA;
    }


    return rc;
}
void print_struct(item_t *items, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%s\n%.6lf\n%.6lf\n", items[i].name, items[i].weight, items[i].volume);
    }
}