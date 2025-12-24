#ifndef MODE_H__
#define MODE_H__

#include "errors.h"
#include "data.h"

typedef enum
{
    NO_PREFIX = 0,
    ALL = 1,
    PRINT_PREFIX = 2,
} mode_t;

error_t handle_args(int argc);
mode_t define_mode(int argc, char **argv);
error_t mode_handler(item_t *items, int count, mode_t mode, const char *prefix);

#endif