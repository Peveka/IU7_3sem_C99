#ifndef MODE_H__
#define MODE_H__

#include "errors.h"
#include "data.h"

typedef enum
{
    ALL = 11,
    NO_PREFIX = 12,
    PRINT_PREFIX = 13,
} mode_t;

error_t handle_args(int argc);
mode_t define_mode(int argc, char **argv);
error_t mode_handler(item_t *items, int count, mode_t mode, const char *prefix);

#endif