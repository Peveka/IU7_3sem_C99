#include <strings.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "data.h"
#include "io.h"
#include "errors.h"
#include "struct_io.h"
#include "struct.h"
#include "struct_sort.h"

static item_t create_struct_item(double mass, double volume, const char *line)
{
    item_t item;
    strncpy(item.name, line, MAX_NAME_LEN - 1);
    item.name[MAX_NAME_LEN - 1] = '\0';
    item.weight = mass;
    item.volume = volume;

    return item; 
}

static error_t analyze_data(const char *mass_line, const char *vol_line, double *mass, double *volume)
{
    error_t rc = OK;
    int mass_scanned = sscanf(mass_line, "%lf", mass);
    int vol_scanned = sscanf(vol_line, "%lf", volume);
    if (mass_scanned == 1 && vol_scanned == 1)
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

static error_t read_name(FILE *file, char *line, size_t line_size)
{
    error_t rc = OK;
    
    if (!file_read_line(file, line, line_size))
    {
        rc = ERROR_FILE_READ;
    }
    else if (strlen(line) == 0) 
    {
        rc = ERROR_INVALID_DATA;
    }
    else if (strlen(line) >= MAX_NAME_LEN)
    {
        rc = ERROR_NAME_TOO_LONG;
    }
    
    return rc;
}

static error_t read_mass_volume(FILE *file, double *mass, double *volume)
{
    error_t rc = OK;
    char mass_line[MAX_LINE_LEN];
    char vol_line[MAX_LINE_LEN];
    
    int mass_read = file_read_line(file, mass_line, sizeof(mass_line));
    int volume_read = file_read_line(file, vol_line, sizeof(vol_line));
    
    if (!mass_read || !volume_read)
    {
        rc = ERROR_NOT_ENOUGH_DATA;
    }
    else
    {
        rc = analyze_data(mass_line, vol_line, mass, volume);
    }
    
    return rc;
}

static error_t scan_item(FILE *file, item_t *item)
{
    error_t rc;
    char line[MAX_LINE_LEN];
    double mass = 0.0, volume = 0.0;
    
    rc = read_name(file, line, sizeof(line));
    if (rc == OK) 
    {
        rc = read_mass_volume(file, &mass, &volume);
    }
        
    if (rc == OK)
    {
        *item = create_struct_item(mass, volume, line);
    }
    
    return rc;
}

error_t handle_struct_scan(item_t *items, const char *filename, int *count_ptr)
{
    error_t rc = OK;
    FILE* file = fopen(filename, "r");
    
    if (file == NULL)
    {
        rc = ERROR_FILE_OPEN;
    }
    else 
    {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        if (file_size == 0)
        {
            rc = ERROR_EMPTY_FILE;
        }
        else
        {
            fseek(file, 0, SEEK_SET);
            int indx = 0;
            
            while (indx < MAX_AR_LEN && rc == OK && !feof(file))
            {
                rc = scan_item(file, &items[indx]);
                if (rc == OK)
                    indx++;
            }

            if (indx == MAX_AR_LEN && !feof(file) && rc == OK)
                rc = ERROR_TOO_MANY_STRINGS;

            if (indx == 0 && rc == OK)
                rc = ERROR_EMPTY_FILE;

            *count_ptr = indx;
        }
        fclose(file);
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