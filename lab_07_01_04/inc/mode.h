#ifndef MODE_H__

#define MODE_H__
#include <string.h>
#include "errors.h"

typedef enum
{
    NO_FILTER = 0,
    FILTER = 1,
    UNKNOWN_MODE = 3
} mode_t;

error_t args_handle(int argc);
mode_t mode_define(int argc, char **argv);

#endif