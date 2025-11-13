#ifndef FILE_IO_H__
#define FILE_IO_H__

#include "list_struct.h"
#include "errors.h"

error_t scan_file_data(const char *filename, node_t **head);
error_t write_file_data(node_t *head, const char *filename);

#endif