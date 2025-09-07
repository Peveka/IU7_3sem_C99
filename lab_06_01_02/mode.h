#ifndef MODE_H__

#define MODE_H__
#include "errors.h"

typedef enum
{
    ALL = 11,
    NO_PREFIX = 12,
    PRINT_PREFIX = 13,
} mode_t;

mode_t define_mode(int argc, char **argv);
error_t mode_handler(int argc, char **argv);
error_t handle_args(int argc);

#endif