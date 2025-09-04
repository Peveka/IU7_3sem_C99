#include <string.h>
#include <math.h>
#include <float.h>
#include "items_io.h"
#include "errors.h"

int read_file_line(FILE *file, char *buf, size_t buf_size) {
    if (!fgets(buf, buf_size, file))
        return 0;

    size_t len = strlen(buf);
    if (len && buf[len - 1] == '\n')
        buf[len - 1] = '\0';

    return 1;
}

int scan_struct(item_t *items, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        errors_handler(ERROR_FILE_OPEN);
        return -ERROR_FILE_OPEN;
    }

    int indx = 0;
    while (indx < MAX_AR_LEN) {
        char line[MAX_LINE_LEN];
        char mass_line[MAX_LINE_LEN];
        char vol_line[MAX_LINE_LEN];

        if (!read_file_line(file, line, sizeof(line)))
            break;

        if (strlen(line) >= MAX_NAME_LEN) 
        {
            errors_handler(TO_LONG_NAME);
            fclose(file);
            return -TO_LONG_NAME;
        }

        if (!read_file_line(file, mass_line, sizeof(mass_line))) 
        {
            errors_handler(NOT_ENOUGH_DATA);
            fclose(file);
            return -NOT_ENOUGH_DATA;
        }

        if (!read_file_line(file, vol_line, sizeof(vol_line))) 
        {
            errors_handler(NOT_ENOUGH_DATA);
            fclose(file);
            return -NOT_ENOUGH_DATA;
        }

        double mass, volume;
        if (sscanf(mass_line, "%lf", &mass) != 1 ||
            sscanf(vol_line, "%lf", &volume) != 1 ||
            mass <= 0.0 || volume <= 0.0 ||
            !isfinite(mass) || !isfinite(volume)) {
            errors_handler(ERROR_INV_DATA);
            fclose(file);
            return -ERROR_INV_DATA;
        }

        strncpy(items[indx].name, line, MAX_NAME_LEN - 1);
        items[indx].name[MAX_NAME_LEN - 1] = '\0';
        items[indx].weight = mass;
        items[indx].volume = volume;
        ++indx;
    }

    fclose(file);
    if (indx == 0) {
        errors_handler(ERROR_EMPTY_FILE);
        return -ERROR_EMPTY_FILE;
    }
    return indx;
}

int print_struct(item_t *items, int count) {
    for (int i = 0; i < count; ++i)
        printf("%s\n%.6lf\n%.6lf\n",
               items[i].name, items[i].weight, items[i].volume);
    return 0;
}