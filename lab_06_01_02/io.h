#ifndef IO_H__

#define IO_H__
#include "errors.h"
#include "data.h"

int file_read_line(FILE* file, char *line, size_t line_size);
error_t analyze_data(const char *mass_line, const char *vol_line, double *mass, double *volume);
void print_struct(item_t *items, int count);

#endif
