#include "mode.h"
#include "errors.h"
#include "struct_io.h"
#include "mem_allocate.h"

int main(int argc, char **argv)
{
    error_t rc = handle_args(argc);
    item_t *items = NULL;
    int count = 0;
    
    if (rc == OK)
    {
        mode_t mode = define_mode(argc, argv);
        char *filename = argv[1];
        const char *prefix = NULL;
        
        if (mode == PRINT_PREFIX)
            prefix = argv[2];
        
        rc = handle_struct_scan(&items, filename, &count);
        if (rc == OK)
            rc = mode_handler(items, count, mode, prefix);
    }

    if (items != NULL)
    {
        struct_free(&items, count);
    }
        
    return rc;
}