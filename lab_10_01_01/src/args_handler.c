#include "errors.h"

error_t args_handler(int argc, char **argv)
{
    error_t rc = OK;
    if (argc != 4)
        rc = ERR_NOT_ENOUGH_DATA;
    return rc;
}