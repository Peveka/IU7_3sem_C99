#ifndef MODE_H__
#define MODE_H__
#include "errors.h"

typedef enum {
    All = 11,
    No_prefix = 12,
    Print_prefix = 13,
} mode_t;

mode_t define_mode(int argc, char** argv);
error_t mode_handler(int argc, char** argv);
error_t handle_args(int argc);

#endif