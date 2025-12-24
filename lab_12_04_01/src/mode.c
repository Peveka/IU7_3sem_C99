#include "mode.h"

error_t args_handle(int argc)
{
    error_t rc = OK;
    if (argc < 3)
        rc = ERROR_NOT_ENOUGH_ARGUMENTS;
    else if (argc > 4)
        rc = ERROR_TOO_MANY_ARGUMENTS;
    
    return rc;
}

mode_t mode_define(int argc, char **argv)
{
    mode_t mode = NO_FILTER;
    if (argc == 4 && !strcmp(argv[3], "f"))
        mode = FILTER;
    else if (argc == 4)
        mode = UNKNOWN_MODE;

    return mode;
}