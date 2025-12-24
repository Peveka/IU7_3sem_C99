#include <stdio.h>

#include "errors.h"
#include "mode.h"

int main(int argc, char **argv)
{
    error_t rc = OK;
    action_mode_t mode = UNKNOWN_MODE;
    matrix_t first_matrix = { 0, 0, NULL};
    matrix_t second_matrix = { 0, 0, NULL};
    matrix_t res_matrix = { 0, 0, NULL};
    rc = mode_define(argc, argv, &mode);
    if (rc == OK)
    {
        switch (mode)
        {
            case ADD_MODE: 
                {
                    rc = add_mode_handler(argv[2], argv[3], argv[4], &first_matrix, &second_matrix, &res_matrix);
                    break;
                }
            case MULTIPLY_MODE: 
                {
                    rc = multiply_mode_handler(argv[2], argv[3], argv[4], &first_matrix, &second_matrix, &res_matrix);
                    break;
                }
            case INVERSE_MATRIX_MODE: 
                {
                    rc = inverse_mode_handler(argv[2], argv[3], &first_matrix, &res_matrix);
                    break;
                }
            case UNKNOWN_MODE: 
                {
                    rc = ERR_UNKNOWN_MODE;
                    break;
                }
        } 
    }
    return rc;
}