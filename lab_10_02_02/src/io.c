#include "stdio.h"
#include "errors.h"
#include "mem_allocation.h"
#include "string.h"

#define MAX_MODE_LEN 5

error_t scan_mode(char *mode)
{
    error_t rc = OK;
    if (fgets(mode, MAX_MODE_LEN, stdin) == NULL)
        rc = ERR_INVALID_DATA;
    else
    {
        size_t len = strlen(mode);
        if (len > 0 && mode[len - 1] == '\n')
            mode[len - 1] = '\0';
    }
    return rc;
}

error_t scan_polynome_coefficients(int **coef_array, int *coeffs_count)
{
    error_t rc = OK;
    if (scanf("%d", coeffs_count) != 1)
        rc = ERR_INPUT_DATA;
    
    if (rc == OK && *coeffs_count <= 0)
        rc = ERR_INVALID_DATA;
        
    if (rc == OK)
        rc = alloc_coef_array(coef_array, *coeffs_count);
        
    for (int i = 0; rc == OK && i < *coeffs_count; ++i)
        if (scanf("%d", (*coef_array) + i) != 1)
        {
            rc = ERR_INPUT_DATA;
            free_coef_data(coef_array);
        }

    return rc;
}

error_t output_polynome_coeffs(int *polynome_coeffs, int polynome_size)
{
    if (!polynome_coeffs || polynome_size < 0)
        printf("0 ");
    else
    {
        for (int i = 0; i < polynome_size; i++)
            printf("%d ", polynome_coeffs[i]);
    } 
    printf("L\n");

    return OK;
}

void output_evaluate_value(int value)
{
    printf("%d\n", value);
}

error_t scan_evaluate_value(int *input_value)
{
    error_t rc = OK;
    if (scanf("%d", input_value) != 1)
        rc = ERR_INPUT_DATA;

    return rc;
}