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

int mode_define(int argc, char **argv)
{
    int mode = 0;
    if (argc == 4 && !strcmp(argv[3], "f"))
        mode = 1;

    return mode;
}