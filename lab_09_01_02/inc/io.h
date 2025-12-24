#ifndef IO_H__
#define IO_H__

#include <stdio.h>
#include "errors.h"

error_t file_read_line(FILE* file, char *line, size_t line_size);

#endif