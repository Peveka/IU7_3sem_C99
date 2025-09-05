#include "struct.h"
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "data.h"
#include "io.h"
#include "errors.h"

int compare_double(double a, double b, double epsilon)
{
    if (fabs(a - b) < epsilon) return 0;
    return ((a > b) ? 1 : -1);
}

void swap_items(item_t* a, item_t* b)
{
    item_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void append_struct_item(double mass, double volume, const char* line, int indx, item_t* items)
{
    strncpy(items[indx].name, line, MAX_NAME_LEN - 1);
    items[indx].name[MAX_NAME_LEN - 1] = '\0';
    items[indx].weight = mass;
    items[indx].volume = volume;
}

void scan_struct(error_t* rc, int* indx, FILE* file, item_t* items)
{
    while (*indx < MAX_AR_LEN && *rc == OK)
    {
        char line[MAX_LINE_LEN];
        char mass_line[MAX_LINE_LEN];
        char vol_line[MAX_LINE_LEN];

        if (!file_read_line(file, line, sizeof(line)))
        {
            *rc = ERROR_INVALID_DATA;
            continue;
        }
        
        if (*rc == OK && strlen(line) >= MAX_NAME_LEN)
        {
            *rc = ERROR_NAME_TOO_LONG;
            continue;
        }

        if (!file_read_line(file, mass_line, sizeof(mass_line)) ||
        !file_read_line(file, vol_line, sizeof(vol_line)))
        {
            *rc = ERROR_NOT_ENOUGH_DATA;
            continue;
        }

        double mass, volume;
        *rc = analyze_data(mass_line, vol_line, &mass, &volume);
        if (rc != OK)
            continue;

        append_struct_item(mass, volume, line, *indx, items);
        ++(*indx);
    }
}

error_t handle_struct_scan(item_t* items, const char* filename, int* count_ptr)
{
    error_t rc = OK;
    FILE* file = fopen(filename, "r");

    if (file == NULL)
        rc = ERROR_FILE_OPEN;
    else 
    {
        int indx = 0;
        scan_struct(&rc, &indx, file, items);

        fclose(file);
        if (indx == 0 && rc == OK)
        {
            rc = ERROR_EMPTY_FILE;
        }

        *count_ptr = indx;
    }

    return rc;
}

void sort_struct(item_t* items, int count)
{
    for (int i = 1; i < count; i++)
    {
        int k = i;
        while (k > 0)
        {
            double ratio1 = items[k - 1].weight / items[k - 1].volume;
            double ratio2 = items[k].weight / items[k].volume;

            if (compare_double(ratio1, ratio2, DBL_EPSILON) > 0)
            {
                swap_items(&items[k - 1], &items[k]);
                k--;
            } else
                break;
        }
    }
}

error_t search_string(item_t* items, int count, const char* prefix)
{
    error_t found = ERROR_STRING_NOT_FOUND;
    for (int i = 0; i < count; i++)
    {
        if (strncmp(items[i].name, prefix, strlen(prefix)) == 0)
        {
            printf("Found: %s\n%.6lf\n%.6lf\n", items[i].name, items[i].weight, items[i].volume);
            found = OK;
        }
    }
    return found;
}