#include <strings.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "io.h"
#include "errors.h"
#include "struct_io.h"
#include "struct.h"
#include "struct_sort.h"
#include "mem_allocate.h"

static void strip_string(char *line)
{
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
    {
        line[len - 1] = '\0';
        len--;
    }
}

static item_t create_struct_item(char *line, double mass, double volume)
{
    item_t item = { line, volume, mass };
    return item; 
}

static error_t check_file_lines_count(FILE *file, int *count)
{
    error_t rc = OK;
    int lines_count = 0;
    char line[MAX_LINE_LEN];
    
    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file) != NULL)
    {
        strip_string(line);
        if (strlen(line) > 0) 
        {
            lines_count++;
        }
    }
    
    if (lines_count == 0)
        rc = ERROR_EMPTY_FILE;
    else if (lines_count % 3 != 0)
        rc = ERROR_NOT_ENOUGH_DATA;
    else
        *count = lines_count / 3;
    
    fseek(file, 0, SEEK_SET);
    return rc;
}

error_t analyze_data(const char *mass_line, const char *vol_line, double *mass, double *volume)
{
    error_t rc = OK;
    char *endptr1, *endptr2;
    
    *mass = strtod(mass_line, &endptr1);
    *volume = strtod(vol_line, &endptr2);
    
    if (endptr1 == mass_line || *endptr1 != '\0')
        rc = ERROR_INVALID_DATA;
    else if (endptr2 == vol_line || *endptr2 != '\0')
        rc = ERROR_INVALID_DATA;
    else if (*mass <= 0.0)
        rc = ERROR_INVALID_DATA;
    else if (*volume <= 0.0)
        rc = ERROR_INVALID_DATA;

    return rc;
}

static error_t read_name(FILE *file, char **name)
{
    error_t rc = OK;
    char line[MAX_LINE_LEN];
    
    rc = file_read_line(file, line, sizeof(line));
    if (rc == OK)
    {
        if (strlen(line) == 0)
            rc = ERROR_INVALID_DATA;
        else
        {
            int name_len = strlen(line);
            rc = name_allocate(name, name_len);
            if (rc == OK)
                strcpy(*name, line);
        }
    }
    
    return rc;
}

static error_t read_mass_volume(FILE *file, double *mass, double *volume)
{
    error_t rc = OK;
    char mass_line[MAX_LINE_LEN];
    char vol_line[MAX_LINE_LEN];
    
    rc = file_read_line(file, mass_line, sizeof(mass_line));
    if (rc == OK)
    {
        rc = file_read_line(file, vol_line, sizeof(vol_line));
        if (rc == OK)
        {
            rc = analyze_data(mass_line, vol_line, mass, volume);
        }
    }
    
    return rc;
}

static error_t scan_item(FILE *file, item_t *item)
{
    error_t rc = OK;
    char *line = NULL;
    double mass = 0.0, volume = 0.0;
    
    rc = read_name(file, &line);
    if (rc == OK)
    {
        rc = read_mass_volume(file, &mass, &volume);
        if (rc == OK)
        {
            *item = create_struct_item(line, mass, volume);
        }
        else
        {
            name_free(&line);
        }
    }
    
    return rc;
}

error_t handle_struct_scan(item_t **items, const char *filename, int *count_ptr)
{
    error_t rc = OK;
    FILE* file = fopen(filename, "r");
    
    if (file == NULL)
    {
        rc = ERROR_FILE_OPEN;
    }
    else 
    {
        int items_count = 0;
        rc = check_file_lines_count(file, &items_count);
        
        if (rc == OK) 
            rc = struct_allocate(items, items_count);
        if (rc == OK)
        {
            int indx = 0;
            while (rc == OK && indx < items_count && !feof(file))
            {
                rc = scan_item(file, *items + indx);
                if (rc == OK)
                    indx++;
                else
                    struct_free(items, indx);
            }
            *count_ptr = indx;
                
            if (indx == 0 && rc != OK)
                rc = ERROR_INVALID_DATA;
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