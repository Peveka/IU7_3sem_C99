#include "mode.h"
#include "errors.h"

int main(int argc, char** argv)
{
    error_t rc = handle_args(argc);
    if (rc == OK)
        rc = mode_handler(argc, argv);

    if (rc != OK)
        handle_error(rc);

    return rc;
}