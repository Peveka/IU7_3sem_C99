#ifndef ITEMS_IO_H
#define ITEMS_IO_H

#include <stdio.h>
#include "errors.h"

#define MAX_AR_LEN 15
#define MAX_NAME_LEN 25
#define MAX_LINE_LEN 100

/**
 * @brief item's structure
 */
typedef struct {
    char name[MAX_NAME_LEN];
    double volume;
    double weight;
} item_t;

/**
 * @brief read line and delete '\n'
 * @return error code or OK 
 */
int read_file_line(FILE *file, char *buf, size_t buf_size);

/**
 * @brief scanning items
 * @return items count or error code
 */
int scan_struct(item_t *items, const char *filename);

/**
 * @brief print getted structure
 */
int print_struct(item_t *items, int count);

#endif // ITEMS_IO_H