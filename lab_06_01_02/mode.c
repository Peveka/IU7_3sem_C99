#include <string.h>
#include <strings.h>
#include "mode.h"
#include "errors.h"
#include "struct.h"
#include "io.h"

mode_t define_mode(int argc, char **argv)
{
    mode_t mode;
    if (argc == 2)
        mode = NO_PREFIX;
    else if (argc == 3 && strcasecmp(argv[2], "ALL") == 0)
        mode = ALL;
    else
        mode = PRINT_PREFIX;

    return mode;
}

error_t mode_handler(item_t *items, int count, mode_t mode, const char *prefix)
{   
    error_t rc = OK;
    switch (mode) 
    {
        case PRINT_PREFIX:
        {
            rc = search_string(items, count, prefix);
            break;
        }
        case NO_PREFIX:
        {
                sort_struct(items, count);
                print_struct(items, count);
                break;
        }
        case ALL:
        {
            print_struct(items, count);
            break;
        }
        
    }
    return rc;
}

error_t handle_args(int argc)
{
    error_t rc = OK;
    if (argc < 2)
    {
        rc = ERROR_NOT_ENOUGH_ARGUMENTS;
    }
    else if (argc > 3)
    {
        rc = ERROR_TOO_MANY_ARGUMENTS;
    }

    return rc;
}