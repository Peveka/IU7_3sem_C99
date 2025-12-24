#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "errors.h"
#include "modes.h"
#include "io.h"
#include "mem_allocation.h"
#include "list_operations.h"
#include "polynom_operations.h"
#include "mode_handler.h"

int main(void)
{
    polynom_t *polynome = NULL;
    modes_t mode;
    error_t rc = define_mode(&mode);
    
    if (rc == OK)
    {
        switch (mode)
        {
            case DDX_MODE:
                rc = ddx_mode_handler(&polynome);
                break;
            case SUM_MODE:
                rc = sum_mode_handler(&polynome);
                break;
            case DVD_MODE:
                rc = dvd_mode_handler(&polynome);
                break;
            case VAL_MODE:
                rc = val_mode_handler(&polynome);
                break;
            default:
                rc = ERR_INVALID_MODE;
                break;
        }
    }

    return rc;
}