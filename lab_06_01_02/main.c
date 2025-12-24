#include "mode.h"
#include "errors.h"
#include "struct_io.h"

int main(int argc, char **argv)
{
    error_t rc = handle_args(argc);
    if (rc == OK)
    {
        mode_t mode = define_mode(argc, argv);
        char *filename = argv[1];
        item_t items[MAX_AR_LEN];
        int count;
        const char *prefix = "No_prefix";
        if (mode == PRINT_PREFIX)
            prefix = argv[2];
        

        rc = handle_struct_scan(items, filename, &count);
        if (rc == OK)
            rc = mode_handler(items, count, mode, prefix);
    }
    return rc;
}