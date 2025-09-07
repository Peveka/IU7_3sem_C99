#include <string.h>
#include <strings.h>
#include "mode.h"
#include "errors.h"
#include "data.h"
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

error_t mode_handler(int argc, char **argv)
{
    char *filename = argv[1];
    item_t items[MAX_AR_LEN];
    mode_t mode = define_mode(argc, argv);
    
    int count;
    error_t rc = handle_struct_scan(items, filename, &count);
    if (rc == OK) 
    {
        switch (mode) 
        {
            case PRINT_PREFIX:
                {
                    rc = search_string(items, count, argv[2]);
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